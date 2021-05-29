#include "tiledata.h"

#if 0

#include <iostream>
#include <Scene/view.h>
#include <Common/utils.h>
#include <cstdio>
#include <QImage>

using namespace std;

TileData::TileData(const char *name, MovableView *v): Data(name), my_view(v) {
    network_mgr = make_unique<QNetworkAccessManager>();
}

void TileData::setRefs(OGRSpatialReference *d, OGRSpatialReference *v) {
    dataref = d;
    viewref = v;
}

void TileData::draw() {
    //cout << "TileData::draw()" << endl;
    if (my_view == nullptr || network_mgr == nullptr)
        return;
    BoundingBox viewBBox = my_view->getDataBBox();
    if (viewBBox != viewDataBBox) {
        // TMP
        //BoundingBox b = my_view->getViewBBox();
        //cout << "New BBox: " << get<0>(b) << " " << get<1>(b) << " " << get<2>(b) << " " << get<3>(b) << endl;
        viewDataBBox = viewBBox;
        int tile_x_min = Utils::long2tilex(viewBBox.x_min, my_view->getZoom());
        int tile_x_max = Utils::long2tilex(viewBBox.x_max, my_view->getZoom());
        int tile_y_min = Utils::lat2tiley(viewBBox.y_min, my_view->getZoom());
        int tile_y_max = Utils::lat2tiley(viewBBox.y_max, my_view->getZoom());
        if (tile_y_min > tile_y_max) swap(tile_y_min, tile_y_max);

        if (tile_x_min != current_tile_x_min || tile_x_max != current_tile_x_max ||
                tile_y_min != current_tile_y_min || tile_y_max != current_tile_y_max) {
            vector<unique_ptr<Tile>> oldTiles;
            swap(oldTiles, vTile);
            current_tile_x_min = tile_x_min;
            current_tile_x_max = tile_x_max;
            current_tile_y_min = tile_y_min;
            current_tile_y_max = tile_y_max;
            //cout << "Required: " << tile_x_min << ", " << tile_x_max << ", " << tile_y_min << ", " << tile_y_max << endl;
            for (int i=tile_x_min-1; i<=tile_x_max+1; ++i)
                for (int j=tile_y_min-1; j<=tile_y_max+1; ++j) {
                    int z = my_view->getZoom();
                    auto it = find_if(begin(oldTiles), end(oldTiles), [i, j, z](const unique_ptr<Tile> &ptr) {
                        return ptr->_x==i && ptr->_y==j && ptr->_zoom==z;
                    });
                    if (it == end(oldTiles)) {
                        vTile.push_back(make_unique<Tile>(z, i, j, dataref, viewref, network_mgr.get()));
                    } else {
                        vTile.push_back(move(*it));
                        oldTiles.erase(it);
                    }
                }
            for (const auto &tile: oldTiles) {
                tile->clean();
            }
            oldTiles.clear();
        }
    }
    glEnable(GL_TEXTURE_2D);
    glColor4d(1.0, 1.0, 1.0, 1.0);
    for (const auto &tile: vTile) {
        tile->draw();
    }
    glDisable(GL_TEXTURE_2D);
    //cout << "TileData::draw() done" << endl;
}/**/

Tile::Tile(int zoom, int x, int y, OGRSpatialReference *d, OGRSpatialReference *v, QNetworkAccessManager *net): QObject(), state(PENDING),
    qnam(net), dataref(d), viewref(v), _zoom(zoom), _x(x), _y(y) {
    char filen[100];
    sprintf(filen, "data/%d-%d-%d.png", zoom, x, y);
    filename = filen;

    double x_min = Utils::tile2utm(_x, _zoom);
    double y_min = Utils::tile2utm(_y + 1, _zoom);
    double x_max = Utils::tile2utm(_x + 1, _zoom);
    double y_max = Utils::tile2utm(_y, _zoom);
    double x_min_wgs84 = Utils::utm2lon(x_min);
    double y_min_wgs84 = Utils::utm2lat(y_min);
    double x_max_wgs84 = Utils::utm2lon(x_max);
    double y_max_wgs84 = Utils::utm2lat(y_max);
    corners_dataref[0].setX(x_min_wgs84); corners_dataref[0].setY(y_min_wgs84);
    corners_dataref[1].setX(x_max_wgs84); corners_dataref[1].setY(y_min_wgs84);
    corners_dataref[2].setX(x_max_wgs84); corners_dataref[2].setY(y_max_wgs84);
    corners_dataref[3].setX(x_min_wgs84); corners_dataref[3].setY(y_max_wgs84);
    for (int i=0; i<4; ++i) {
        corners_dataref[i].assignSpatialReference(dataref);
        corners_viewref[i] = corners_dataref[i];
        corners_viewref[i].transformTo(viewref);
        //cout << "Tile coords: " << i << ": " << corners_viewref[i].getX() << ", " << corners_viewref[i].getY() << endl;
    }

    QString file_as_qstring = QFile::decodeName(filename.c_str());
    if(QFile::exists(file_as_qstring)) {
        state = AVAILABLE;
    } else if (qnam != nullptr) {
        char curl[150];
        sprintf(curl, "http://pc-gi-44.utbm.fr/osm_tiles/%d/%d/%d.png", zoom, x, y);
        QUrl url(tr(curl));
        reply = qnam->get(QNetworkRequest(url));
        connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));
    }
}

void Tile::replyFinished() {
    QString filen(filename.c_str());
    qint64 size = reply->bytesAvailable(), bytes_read;
    char *buffer = new char[size];
    bytes_read = reply->read(buffer, size);
    QFile f(filen);
    if (size != 0 && bytes_read == size && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200
            && f.open(QIODevice::WriteOnly) && dataref != nullptr && viewref != nullptr) {
        //cout << "Received tile " << _zoom << " " << _x << " " << _y << " of size " << size  << "(read: " << bytes_read << ")" << endl;
        f.write(buffer, size);
        f.close();
        state = AVAILABLE;
    }
    reply->deleteLater();
}

void Tile::draw() {
    if (state == AVAILABLE && textr != nullptr && textr->textureId() != 0) {
        //cout << "Draw tile " << _zoom << "/" << _x << "/" << _y << ".png" << endl;
        if (list_index == 0) {
            if ((list_index = glGenLists(1)) == 0)
                return;
            glNewList(list_index, GL_COMPILE);
            textr->bind();
            glColor4d(1.0, 1.0, 1.0, 0.7);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);
                glVertex3d(corners_viewref[0].getX(), corners_viewref[0].getY(), -0.1);
                glTexCoord2f(1.0, 0.0);
                glVertex3d(corners_viewref[1].getX(), corners_viewref[1].getY(), -0.1);
                glTexCoord2f(1.0, 1.0);
                glVertex3d(corners_viewref[2].getX(), corners_viewref[2].getY(), -0.1);
                glTexCoord2f(0.0, 1.0);
                glVertex3d(corners_viewref[3].getX(), corners_viewref[3].getY(), -0.1);
            glEnd();
            glEndList();
        }
        if (list_index != 0) {
            glCallList(list_index);
        }
    }
    if (state == AVAILABLE && textr == nullptr) {
        textr = make_unique<QOpenGLTexture>(QImage(filename.c_str()).mirrored());
        textr->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        textr->setMagnificationFilter(QOpenGLTexture::Linear);
    }
}

void Tile::clean() {
    if (textr != nullptr && textr->textureId() != 0)
        textr->destroy();
    if (list_index != 0)
        glDeleteLists(list_index, 1);
}

#endif
