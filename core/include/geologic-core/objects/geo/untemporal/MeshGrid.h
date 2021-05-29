/**
 * \file	MeshGrid.h
 */

#ifndef MeshGrid_H
#define MeshGrid_H

#include "ogr_geometry.h"
#include <unordered_map>

template <typename T> class MeshGrid {

    public:
        //*/ -------------------------------------------------
        using Position = std::pair<int, int>;

        std::unordered_map<Position, T>& getGrid() {return grid;}
        const std::unordered_map<Position, T>& getGrid()const {return grid;}
        T& get(int i, int j) noexcept(false) {return grid.at({i, j});}
        const T& get(int i, int j)const noexcept(false) {return grid.at({i, j});}

    private:
        //*/ -------------------------------------------------
        std::unordered_map<Position, T> grid;    ///< the content of the grid, one element for each mesh with information
        OGRPoint origin;               ///< its point of origin (with its attached spatial reference).
        double mesh_x_length;           ///< the width of each mesh (in _origin spatial reference units)
        double mesh_y_length;           ///< the height of each mesh (in _origin spatial reference units)
        int x_count;                    ///< the number of meshes on the x coordinate (from left to right)
        int y_count;                    ///< the number of meshes on the y coordinate (from bottom to top)
};

#endif // MeshGrid_H
