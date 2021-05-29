#pragma once

#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <Scene/movableview.h>
#include <geologic-core/utils/customToolbox.h>
#include <geologic-core/algorithms/geoMetrics/geoMetrics.h>
#include <geologic-core/objects/geo/untemporal/Bbox.h>
#include <ogr_spatialref.h>
#include <Object/generatorobject.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <QtOpenGL/QtOpenGL>

#include <ResourceManagement/texturedownloader.h>
#include <ResourceManagement/datamanager.h>

using std::cout;
using std::endl;

/*!
 * \class TileGrid manages a grid of tiles one one type.
 * TileGrid class is in charge of getting the screen footprint,
 * computing the tile indices covering the footprint, creating
 * the tiles, cleaning the tiles and update the list of tiles
 * required when the screen moves or resizes.
 */
template <typename T>
class TileGrid: public GeneratorObject {
private:
    std::vector<std::unique_ptr<T>> m_grid;    ///< The actuel content of the grid, one tile in each element
    MovableView* m_my_view;                          ///< view managing the tile grid, provided by the owner of TileGrid
    Bbox m_viewDataBBox;                             ///< Current view bounding box in data spatial reference, used to update the grid
    OGRPoint m_centerDataView;                       ///< Current view center in data spation reference, used to update the grid
    Bbox m_currentTileBbox;                          ///< Current bounding box in tile coordinates
    int m_currentZoom;
    bool m_first_time = true;

public:
    TileGrid() = delete;
    TileGrid(std::string& name, MovableView* view):
        TileGrid(name.c_str(), view) {}

    TileGrid(const char *name, MovableView *view);

    virtual void update(QMatrix4x4 &model, double t);
    virtual ~TileGrid() {}
};

template <typename T>
TileGrid<T>::TileGrid(const char *name, MovableView *view):
    GeneratorObject(view, name), m_my_view(view) {
}


template <typename T>
void TileGrid<T>::update(QMatrix4x4 &model, double t) {
    GeneratorObject::update(model, t);
    if(!m_hidden) {
        if (m_my_view == nullptr)
            return;
        //std::cout << " start" << std::endl;
        Bbox viewBBox = m_my_view->getDataBBox();
        OGRPoint centerView = m_my_view->getCenterInDataRef();
        if (viewBBox != m_viewDataBBox || centerView != m_centerDataView) {

            m_first_time = false;
            m_viewDataBBox = viewBBox;
            m_centerDataView = centerView;

            int z = m_my_view->getZoom();
            m_currentZoom = z;
            int grid_size = pow(2, z);
            int grid_max = grid_size - 1;
            int tile_x_min = geoMetrics::long2tilex(viewBBox.minx, m_my_view->getZoom()) - 1;
            if (tile_x_min < 0) tile_x_min = 0;
            if (tile_x_min > grid_max) tile_x_min = grid_max;
            int tile_x_max = geoMetrics::long2tilex(viewBBox.maxx, m_my_view->getZoom()) + 1;
            if (tile_x_max < 0) tile_x_max = 0;
            if (tile_x_max > grid_max) tile_x_max = grid_max;
            int tile_y_min = geoMetrics::lat2tiley(viewBBox.maxy , m_my_view->getZoom()) - 1;
            if (tile_y_min < 0) tile_y_min = 0;
            if (tile_y_min > grid_max) tile_y_min = grid_max;
            int tile_y_max = geoMetrics::lat2tiley(viewBBox.miny , m_my_view->getZoom()) + 1;
            if (tile_y_max < 0) tile_y_max = 0;
            if (tile_y_max > grid_max) tile_y_max = grid_max;

            if (tile_x_min != m_currentTileBbox.minx || tile_x_max != m_currentTileBbox.maxx ||
                tile_y_min != m_currentTileBbox.miny || tile_y_max != m_currentTileBbox.maxy) {
                std::vector<std::unique_ptr<T>> oldTiles;
                std::swap(oldTiles, m_grid);
                m_currentTileBbox = std::make_tuple(tile_x_min, tile_y_min, tile_x_max, tile_y_max);
                for (int base_i = tile_x_min; base_i<=tile_x_max; ++base_i) {
                    int i = base_i;
                    if (i < 0) i = 0;
                    if (i > grid_max) i = grid_max;
                    for (int base_j = tile_y_min; base_j<=tile_y_max; ++base_j) {
                        int j = base_j;
                        auto it = std::find_if(begin(oldTiles), end(oldTiles), [i, j, z, grid_size](const std::unique_ptr<T> &ptr) {
                            return ptr->m_x==i && ptr->m_y==j && ptr->m_zoom==z;
                        });
                        if (it == std::end(oldTiles)) {
                            m_grid.push_back(std::make_unique<T>(getView(), base_i, base_j, z));
                        } else {
                            m_grid.push_back(std::move(*it));
                            oldTiles.erase(it);
                        }
                    }
                }
                oldTiles.clear();
            }
            for (const auto &tile: m_grid) {
                tile->update(m_proxy_model, t);
            }
        }
    }
}
