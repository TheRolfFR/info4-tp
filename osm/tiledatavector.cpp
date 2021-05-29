#include "tiledatavector.h"

#if 0

#include <iostream>
#include <Scene/view.h>
#include <Common/utils.h>
#include <OpenGL/linedisplayer.h>
#include <Scene/movableview.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QFile>
#include <tagsbuilder.h>

using namespace std;

TileDataVector::~TileDataVector() {}

TileDataVector::TileDataVector(const char *name, Color *c, MovableView *v): Data(name), parent_view(v), _color(c) {
    qnam = make_unique<QNetworkAccessManager>();
}

void TileDataVector::draw() {
    if (parent_view == nullptr || qnam == nullptr)
        return;
    BoundingBox viewBBox = parent_view->getDataBBox();
    if (viewBBox != viewDataBBox) {
        viewDataBBox = viewBBox;
        int tile_x_min = Utils::long2tilex(viewBBox.x_min, parent_view->getZoom());
        int tile_x_max = Utils::long2tilex(viewBBox.x_max, parent_view->getZoom());
        int tile_y_min = Utils::lat2tiley(viewBBox.y_min, parent_view->getZoom());
        int tile_y_max = Utils::lat2tiley(viewBBox.y_max, parent_view->getZoom());
        if (tile_y_min > tile_y_max) swap(tile_y_min, tile_y_max);

        if (tile_x_min != current_tile_x_min || tile_x_max != current_tile_x_max ||
                tile_y_min != current_tile_y_min || tile_y_max != current_tile_y_max) {
            vector<unique_ptr<VectorTile>> oldTiles;
            swap(oldTiles, vTile);
            current_tile_x_min = tile_x_min;
            current_tile_x_max = tile_x_max;
            current_tile_y_min = tile_y_min;
            current_tile_y_max = tile_y_max;
            //cout << "Required: " << tile_x_min << ", " << tile_x_max << ", " << tile_y_min << ", " << tile_y_max << endl;
            for (int i=tile_x_min-1; i<=tile_x_max+1; ++i)
                for (int j=tile_y_min-1; j<=tile_y_max+1; ++j) {
                    int z = parent_view->getZoom();
                    auto it = find_if(begin(oldTiles), end(oldTiles), [i, j, z](const unique_ptr<VectorTile> &ptr) {
                        return ptr->_x==i && ptr->_y==j && ptr->_zoom==z;
                    });
                    if (it == end(oldTiles)) {
                        vTile.push_back(make_unique<VectorTile>(z, i, j, qnam.get(),
                                                                parent_view->getGeoRefs()->getViewRef(),
                                                                parent_view->getGeoRefs()->getDataRef(), _color));
                    } else {
                        vTile.push_back(move(*it));
                        oldTiles.erase(it);
                    }
                }
            for (const auto &tile: oldTiles) {
                if (tile != nullptr)
                    tile->clean();
            }
            oldTiles.clear();
        }
    }
    for (const auto &tile: vTile) {
        tile->draw();
    }
}

void VectorTile::replyFinished() {
    QString filen(filename.c_str());
    qint64 size = reply->bytesAvailable(), bytes_read;
    char *buffer = new char[size];
    bytes_read = reply->read(buffer, size);
    QFile f(filen);
    if (size != 0 && bytes_read == size && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200
            && f.open(QIODevice::WriteOnly)) {
        f.write(buffer, size);
        f.close();
        _roads = make_unique<Roads>();
        _roads->setLoader(new OSMRouteLoader(_dataref));
        _roads->load(filename.c_str());
        auto &mEdge = _roads->getmEdge();
        for (auto &edge: mEdge) {
            edge.second->getNodes()->transformTo(_to);
        }/**/
        loaded = true;
    }
    reply->deleteLater();
}

VectorTile::VectorTile(int zoom, int x, int y, QNetworkAccessManager *net, OGRSpatialReference *to, OGRSpatialReference *data, Color *c = nullptr):
        QObject(), qnam(net), _to(to), _dataref(data), _color(c), _zoom(zoom), _x(x), _y(y) {
    char filen[100];
    sprintf(filen, "data/%d-%d-%d.osm", zoom, x, y);
    filename = filen;
    double bbox[4];

    QString file_as_qstring = QFile::decodeName(filename.c_str());
    if(QFile::exists(file_as_qstring)) {
        _roads = make_unique<Roads>();
        _cThread = make_unique<ConvertorThread>(_roads.get(), _dataref, _to, filename, this);
        _cThread->start();
    } else if (qnam != nullptr) {
        bbox[1] = Utils::utm2lon(Utils::tile2utm(_x, _zoom));
        bbox[0] = Utils::utm2lat(Utils::tile2utm(_y + 1, _zoom));
        bbox[3] = Utils::utm2lon(Utils::tile2utm(_x + 1, _zoom));
        bbox[2] = Utils::utm2lat(Utils::tile2utm(_y, _zoom));
        TagsBuilder tb;
        tb.setBoudingBox(bbox);
        tb.setoutputformat("xml");
        tb.is("highway");

        //cout << tb.toString() << endl;
        QUrl url(tr(tb.toString().c_str()));
        reply = qnam->get(QNetworkRequest(url));
        connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));
    }
}

void VectorTile::draw() {
    if (loaded) {
        if (list_index == 0) {
            if ((list_index = glGenLists(1)) == 0)
                return;
            const auto &mEdge = _roads->getmEdge();
            glNewList(list_index, GL_COMPILE);
            for (const auto &edge: mEdge) {
                LineDisplayer::draw(edge.second->getNodes(), _color, 1.0, _to);
            }
            glEndList();
            _roads.reset();
        }
        if (list_index != 0) {
            glCallList(list_index);
        }
    }
}

void VectorTile::clean() {
    if (list_index != 0)
        glDeleteLists(list_index, 1);
    cancelled = true;
    if (_cThread != nullptr)
        _cThread->wait();
}

void ConvertorThread::run() {
    _roads->setLoader(new OSMRouteLoader(_from));
    _roads->load(_filename.c_str());
    auto &mEdge = _roads->getmEdge();
    for (auto &edge: mEdge) {
        if (_tile != nullptr && _tile->cancelled == true)
            break;
        edge.second->getNodes()->transformTo(_to);
    }
    if (_tile != nullptr)
        _tile->loaded = true;
}

#endif
