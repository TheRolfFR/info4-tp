#ifndef TILEDATAVECTOR_H
#define TILEDATAVECTOR_H

#if 0

#include <Data/data.h>
#include <vector>
#include <string>
#include <memory>
#include <QObject>
#include <QNetworkAccessManager>
#include <Scene/movableview.h>
#include <roads.h>
#include <Common/color.h>
#include <QtOpenGL/QtOpenGL>
#include <osmrouteloader.h>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>

class TileCacheVector;
class View;
class GLDisplay;
class VectorTile;

class ConvertorThread: public QThread {
    Q_OBJECT

    Roads *_roads;
    OGRSpatialReference *_from;
    OGRSpatialReference *_to;
    std::string _filename;

public:
    ConvertorThread(Roads *r, OGRSpatialReference *from, OGRSpatialReference *to, const std::string &filename, VectorTile *v):
        QThread(), _roads(r), _from(from), _to(to), _filename(filename), _tile(v) {}
    void run();
    VectorTile *_tile;
};

struct VectorTile: public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager *qnam;
    std::string filename;
    QNetworkReply *reply = nullptr;
//    bool downloaded = false;
    GLuint list_index = 0;
    OGRSpatialReference *_to;
    OGRSpatialReference *_dataref;
    Color *_color;
    std::unique_ptr<Roads> _roads;
    std::unique_ptr<ConvertorThread> _cThread;

public:
    VectorTile(int zoom, int x, int y, QNetworkAccessManager *net, OGRSpatialReference *_to, OGRSpatialReference *data, Color *_color);
    ~VectorTile() {}
    void draw();
    void clean();
    bool operator==(const VectorTile &other) {return _zoom==other._zoom && _x==other._x && _y==other._y;}

    int _zoom;
    int _x;
    int _y;
    bool loaded = false;
    bool cancelled = false;

public slots:
    void replyFinished();
};

/*!
 * \brief The TileDataVector class used to draw data taken from OSM files
 */
class TileDataVector: public Data
{

private:
    Roads roads;
    MovableView *parent_view;
    std::unique_ptr<QNetworkAccessManager> qnam;
    std::vector<std::unique_ptr<VectorTile>> vTile;
    Color *_color;
    BoundingBox viewDataBBox;
    int current_tile_x_min = 0;
    int current_tile_x_max = 0;
    int current_tile_y_min = 0;
    int current_tile_y_max = 0;

public:

    /*!
     * \brief TileDataVector is the constructor
     * \param name the data name, used for display purpose
     * \param c the drawing color
     * \param v the view in which to draw the data
     */
    TileDataVector(const char *name, Color *c, MovableView *v);

    void draw();
    void draw(unsigned long long t) {t = t;draw();}

    ~TileDataVector();
};

#endif

#endif // TILEDATAVECTOR_H
