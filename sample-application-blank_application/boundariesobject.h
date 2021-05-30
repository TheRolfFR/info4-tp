#ifndef BOUNDARIESOBJECT_H
#define BOUNDARIESOBJECT_H

#include "Object/childobject.h"
#include "boundariesmaterial.h"
#include "boundariesdata.h"
#include "OpenGL/loadingmanager.h"

class BoundariesObject: public ChildObject {
public:
    BoundariesObject(View *v): ChildObject("BoundariesObject") {
        m_render_layer = v->addRenderObject("zone", this);
        auto mat = std::make_shared<BoundariesMaterial>();
        setMaterial(mat);
        auto data = std::make_shared<BoundariesData>();
        setData(data);
        LoadingManager::getInstance()->load(data);
        data->setPreloaded(true);
    }
   ~BoundariesObject() {}
   void draw(Shader* shader) {
       ChildObject::draw(shader);
   }
};

#endif // BOUNDARIESOBJECT_H
