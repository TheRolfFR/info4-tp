#ifndef TILEDATA_H
#define TILEDATA_H

#if 0

#include <Scene/movableview.h>
#include <QObject>
#include <QtOpenGL/QtOpenGL>
//#include <OpenGL/texture.h>
#include <Data/staticdata.h>
#include <ogr_geometry.h>
#include <ogr_spatialref.h>
#include <vector>
#include <string>
#include <memory>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class TileCache;
class View;
class GLDisplay;
class TexturedPolygonDisplayer;

class Tile: public QObject {
    Q_OBJECT

    enum {PENDING, AVAILABLE} state;
    //std::unique_ptr<Texture> texture;
    OGRPoint corners_dataref[4];
    OGRPoint corners_viewref[4];
    QNetworkAccessManager *qnam;
    OGRSpatialReference *dataref;
    OGRSpatialReference *viewref;
    std::string filename;
    std::unique_ptr<QOpenGLTexture> textr;
    QNetworkReply *reply = nullptr;
    GLuint list_index = 0;

public:
    Tile(int zoom, int x, int y, OGRSpatialReference *d, OGRSpatialReference *v, QNetworkAccessManager *net = nullptr);
    ~Tile() {}
    void draw();
    void clean();

    int _zoom;
    int _x;
    int _y;

public slots:
    void replyFinished();
};

class TileData: public Data {
protected:
    std::unique_ptr<QNetworkAccessManager> network_mgr;
    std::vector<std::unique_ptr<Tile>> vTile;
    MovableView *my_view;
    OGRSpatialReference *dataref;
    OGRSpatialReference *viewref;
    BoundingBox viewDataBBox;
    int current_tile_x_min = 0;
    int current_tile_x_max = 0;
    int current_tile_y_min = 0;
    int current_tile_y_max = 0;

public:
    TileData(std::string& name, MovableView *v): TileData(name.c_str(), v) {}
    TileData(const char *name, MovableView *v);

    void setRefs(OGRSpatialReference *d, OGRSpatialReference *v);
    virtual void draw();
    virtual void draw(unsigned long long t) {draw();}
    ~TileData() {}
};
/**/
#endif

#endif // TILEDATA_H
