# Geologic manual

Table of Content

- [Installation](#installation)
- [Example 1: static data](#first-example)
- [Example 2: static textured data](#example-2)
- [Example 3: dynamic data](#second-example)

## Installation

To install geologic, you shall compile it.

### Fedora

geologic-core

- shapelib: shapelib-devel
- GeographicLib: GeographicLib-devel

geologic-osm

- readosm: readosm-devel
- glut: freeglut-devel

geologic-gui

MobilityVanet

- GDAL: gdal-dev

### Ubuntu

TODO

## First example

This example aims at displaying static data. Here, we'll be displaying the boundaries of mainland France.

### Basic understanding of the underlying concepts

Before diving into the code, let's present the basic concepts required to write an application based on the geologic set of libraries. Libgeologic-gui is the main component of a geologic application. It relies on a pipeline in which users of the library plug their data and processing, which will be then updated and displayed without requiring knowledge of all the OpenGL status.

The main class of a geologic application is a child of the SceneManager class. This class embeds a main view, which is scrollable, zoomable and can play an accelerated mobility simulation or traces replay. The main view contains two components used for displaying data:
- a render tree: it consists of layers, each layer having its shaders, and connected objects to be rendered to screen
- an update tree: it consists in a hierarchy of objects, with a parent-child relation meaning that the child is geographically linked to its parent (i.e. the parent movement also applies on its children)

Objects are defined with several links to other resources:
- the data: a child of the Data class, which contains the actual vertices and other relevant information for OpenGL rendering.
- a material: child of Material class, it defines the rendering color or texture.
- The object is also linked to the render tree and the update tree (both having collections of objects references)

### Introduction

The first step is to subclass the geologic-gui SceneManager class. Your constructor must call the SceneManager constructor as well:

```cpp
#include <OpenGL/scenemanager.h>

class MyGeologicBaseClass: public SceneManager {
public:
	MyGeologicBaseClass();
	virtual ~MyGeologicBaseClass();
};

MyGeologicBaseClass::MyGeologicBaseClass(): SceneManager() {
	// Do your constructing here
}
```

The following methods are required from the SceneManager class (you shall override those):
```cpp
class MyGeologicBaseClass: public SceneManager {
    /* ... */
	
	virtual void init();
	virtual void draw();
	virtual double update();
	virtual void realUpdate(double t);
	virtual void resize(QVector2D& size);
};
```
Each function first calls the SceneManager implementation (for instance in `MyGeologicBaseClass::init`, you shall first call `SceneManager::init();` Then, you have to subclass an object class (either object or one of its children)

We need to subclass some of the libgeologic-gui in order to be able to display elements. These classes (or one of their more specialized children) are:

- Object: in our example, we'll subclass ChildObject. This is a basic object class implementation and the basic type that can be inserter both into the render tree and the update tree.
- Material: it defines colors or textures used to render an object.
- Data: it defines the actual 3D data, including its vertices. Here, we'll be using its child class UniqueData.

With this in mind, we'll use the implementations defined below.

### The BoundariesMaterial class

This class is pretty simple. The only relevant code is in its constructor. Line 3, we must call its parent class constructor. On line 4, we define a color named `"diffuse"`. The `"diffuse"` name will be transfered to the GPU and the relevant fragment shader as a uniform value with this name, and the 4 floating point values defining a semi-transparent white (255, 255, 255, 0.5). Display mode is set to `GL_LINE` on line 5 to display only the boundaries borders (not filling the interior).

```cpp
1 class BoundariesMaterial: public Material {
2 public:
3     BoundariesMaterial(): Material("BoundariesMaterial") {
4         setColor("diffuse", Color{255.0f, 255.0f, 255.0f, 0.5f});
5         setDisplayMode(GL_LINE);
6     }
7     virtual ~BoundariesMaterial() {}
8 };
```

Here is the `"zone"` fragment shader code, in which we notice the `"diffuse"` uniform parameter.

```glsl
#version 330

uniform vec4 diffuse;
out vec4 outColor;

void main( void )
{
 	outColor = diffuse;
}
```

### The BoundariesObject class

This class is simple enough to be defined inside its declaration. There are some key points in this code. On line 3, we call the parent class constructor, required to initialize object related members. On line 4, it is critical that the first parameter of the `addRenderObject` method call is the same than that of the layer it will be managed by. We'll go back to this later. Lines 5 and 6 instantiate and link a material to our object, while lines 7 and 8 provide its data. Finally, `LoadingManager::getInstance()->load` must be called to allow to initialize the OpenGL buffers when a screen update is called. Line 10, we mark the data as preloaded, so that the call of `LoadingManager::getInstance()->update` can indeed initialize the data OpenGL buffers. Without this last instruction, the data would never appear on screen.

The draw method simply calls its parent (which ironically is a ChildObject).

```cpp
01 class BoundariesObject: public ChildObject {
02 public:
03     BoundariesObject(View *v): ChildObject("BoundariesObject") {
04         m_render_layer = v->addRenderObject("zone", this);
05         auto mat = std::make_shared<MyMaterial>();
06         setMaterial(mat);
07         auto data = make_shared<MyData>();
08         setData(data);
09         LoadingManager::getInstance()->load(data);
10         data->setPreloaded(true);
11     }
12    ~BoundariesObject() {}
13    void draw(Shader* shader) {
14        ChildObject::draw(shader);
15    }
16 };
```

### The BoundariesData class

This class is the most complex, due to the loading of the data. Here is the class declaration. It only overrides some of its `UniqueData` parent class. We'll look at the individual methods below.

```cpp
class BoundariesData: public UniqueData {
public:
    BoundariesData();
    ~BoundariesData() {}
    void draw();
};
```

Most of the job is achieved in the constructor as displayed below. In it, we call the parent class constructor (line 1). Then, we specialize our class. First, we declare a `tmp_vertices` vector to store the data that will be used by our class (line 2). Then, we import the data by using GDAL and OGR (lines 3 to 10). Then, we assign the data coordinate reference to the outer boundary (line 11). On line 12, we create a coordinate transformation to project our points from the data coordinate reference to the view coordinate reference. On line 13, we apply the transformation, before deleting it on line 14. Then (lines 15-21), we loop over all points in the boundary, we extract it and copy its coordinates to the temporary vector. On line 22, we set the data vertices to the content of the temporary vertices. On line 23, we define to the data class that it will have to display a line strip (i.e. linked lines whose points are a series, see `GL_LINE_STRIP` definition for more information). Finally, on line 24, we free the dataset since it has become irrelevant.

```cpp
01 MyData::MyData(): UniqueData("MyData") {
02     vector<float> tmp_vertices;
03     GDALAllRegister();
04     GDALDataset *ds = openOsm("france-boundaries.osm");
05     OGRLayer *layer = ds->GetLayer(3);
06     OGRFeature *feature = layer->GetNextFeature();
07     OGRGeometry *geometry = feature->GetGeometryRef();
08     OGRMultiPolygon *boundaries = reinterpret_cast<OGRMultiPolygon *>(geometry);
09     OGRPolygon *france_mainland = reinterpret_cast<OGRPolygon *>(boundaries->getGeometryRef(64)); // We tried before, so we know it is 64
10     OGRLinearRing *france_outer = france_mainland->getExteriorRing();
11     france_outer->assignSpatialReference(CoordinateSystemManager::getInstance()->getDataRef());
12     OGRCoordinateTransformation *t = OGRCreateCoordinateTransformation(
                                        CoordinateSystemManager::getInstance()->getDataRef(),
                                        CoordinateSystemManager::getInstance()->getViewRef());
13     if (t) france_outer->transform(t);
14     OCTDestroyCoordinateTransformation(t);
15     for (int i=0; i<france_outer->getNumPoints(); ++i) {
16         OGRPoint p;
17         france_outer->getPoint(i, &p);
18         tmp_vertices.push_back(p.getX());
19         tmp_vertices.push_back(p.getY());
20         tmp_vertices.push_back(0.0);
21     }
22     setVertices(tmp_vertices);
23     setStructureType(GL_LINE_STRIP);
24     GDALClose(ds);
25 }
```

### Glueing all of these classes together

The last step is now to link all those classes to the library framework so that it will enter the application rendering flow. It is achieved in the `MyScene::init()` method as illustrated below.

```cpp
void MyScene::init() {
    SceneManager::init();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    getMainView()->addLayer("zone"); // Adding a new layer named 'zone' which links to shaders zone; TODO: create own shader!

    MyObject *my_object = new MyObject(getMainView());
    getMainView()->addObject(my_object);

    getController()->bindWheel(1, [this]() {
        getMainView()->zoomIn();
        needsViewUpdate();
    });

    getController()->bindWheel(-1, [this]() {
        getMainView()->zoomOut();
        needsViewUpdate();
    });

    getController()->bindDrag(Qt::LeftButton, [this](QVector2D, QVector2D, QVector2D offset) {
        getMainView()->moveViewCenter((int)offset.x(), -(int)offset.y());
        needsViewUpdate();
    });

    getController()->bindMove([this](QVector2D pos, QVector2D) {
        double x = getMainView()->getViewXMin() + ((getMainView()->getViewXMax() - getMainView()->getViewXMin()) * pos.x() / getMainView()->getScreenWidth());
        double y = getMainView()->getViewYMin() + ((getMainView()->getViewYMax() - getMainView()->getViewYMin()) * (getMainView()->getScreenHeight() - pos.y()) / getMainView()->getScreenHeight());
        updateLabel(QVector2D(x, y));
    });
}
```

This code is divided into 3 main parts: initialization, instanciation of data/objects, and controller definition. Let start with the initialization: it starts with `SceneManager::init();`, which calls the init method of the parent class, then it defines the main OpenGL features.

The second part starts with adding a layer (in the example, it is named `"zone"`) to the main view. Take note that the name of the layer must match the name of the shader folder in which the fragment and vertex shaders related to the layer will be located. Also note that the order which layers are created is the order they will be rendered. So, when disabling depth buffer, remember to first add layers which are a background (raster maps for instance) and only then layers that are mostly empty (i.e. vector data). Then, a new MyObject is created and linked to the view render tree. Finally, we add the object to the view update tree.

The third part defines controllers actions (here, we define left click-drag to slide the view footprint, and wheel up and down to zoom in and out).

## Second example

For this second example, the use case consists in drawing a 20km radius disc around a location. It is related to the 2020 France second lockdown during which people were allowed to go exercising outdoors within a 20km radius from home.

Our choice for this example will be to use a PNG picture as a disc texture. The disc is white and its background is transparent. Classes are prefixed with Circle in the example.

### Circle data class

```cpp
class CircleData: public UniqueData {
private:
    OGRPoint _center;
public:
    CircleData(): UniqueData("Distance circle") {
        _center.setX(6.9151880);
        _center.setY(47.6089977);
        _center.assignSpatialReference(CoordinateSystemManager::getInstance()->getDataRef());
        _center.transformTo(CoordinateSystemManager::getInstance()->getViewRef());
        _center.setZ(1.0);
        cout << "Center (" << _center.getX() << ", " << _center.getY() << ")" << endl;
        float xc = static_cast<float>(_center.getX());
        float yc = static_cast<float>(_center.getY());
        float radius = 20000.0f;
        vector<float> vertices = {
            xc-radius, yc-radius, 1.0f,
            xc-radius, yc+radius, 1.0f,
            xc+radius, yc-radius, 1.0f,
            xc+radius, yc+radius, 1.0f,
            xc+radius, yc-radius, 1.0f,
            xc-radius, yc+radius, 1.0f,
        };
        vector<float> uvs = {
            0, 0,
            0, 1,
            1, 0,
            1, 1,
            1, 0,
            0, 1,
        };
        setVertices(vertices);
        setUVs(uvs);
        setStructureType(GL_TRIANGLES);
    }
    virtual ~CircleData() {}
};
```

This class only needs to implement its constructor and an empty destructor. In the constructor, the main steps are:
- Setting the center coordinates (for the example, they are fixed)
- Converting the coordinates from WGS84 to the coordinate reference used to display (although using a global mercator projection messes the distances, you ought to use EPSG:2154, the local Lambert93 projection)
- Assigning the coordinates of the square (rendered as two triangles) on which the texture will be applied.
- Assigning the texture coordinates to the square vertices.
- Finally, we set the vertices, texture coordinate and primitive type in the parent class.

Basically, this class defines a square centered on the coordinate of the disc center.

### Circle material class

Here, there is no need for a dedicated class, so we instantiate a Material object (see below in the object class). Using base classes whenever possible is a good practice to avoid maintaining too much code and to avoid having duplicates.

### Circle object class

```cpp
class MyCircleObject: public ChildObject {
    OGRPoint _center;
public:
    MyCircleObject(View *v): ChildObject("My circle") {
        m_render_layer = v->addRenderObject("my_circle", this);
        std::shared_ptr<Material> mat = make_shared<Material>("my_circle");
        shared_ptr<Texture> tex = make_shared<Texture>();
        tex->loadFromFile("Textures/disque.png");
        if (!tex->isReady()) cout << "Could not load texture" << endl;
        mat->setTexture("tileTexture", move(tex));
        mat->setDisplayMode(GL_FILL);
        mat->setOption(GL_DEPTH_TEST, false);
        setMaterial(mat);

        shared_ptr<Data> data = make_shared<CircleData>();
        setData(data);
        LoadingManager::getInstance()->load(data);
        data->setPreloaded(true);
    }
    virtual ~MyCircleObject() {}
    void draw(Shader* shader) {
        if (m_data->getLoaded()) {
            m_data->bind();
        }
        ChildObject::draw(shader);
    }
};
```

Here we define a disc object. It is centered on its _center member. The constructor flow is similar to the one from the first example. There is however a noticeble change for the draw method. It requires binding the texture, a step which is not handled directly in the parent object.

## Third example

