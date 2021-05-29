#ifndef MESH_HPP
#define MESH_HPP

#include <map>
#include <ogr_geometry.h>
#include <ogr_spatialref.h>
#include <vector>
#include <set>
#include <limits>
#include <geologic-core/utils/customToolbox.h>

#include <iostream>

/*!
 * \class Mesh defines a sparse grid mesh
 */
template <typename T>
class Mesh {
public:
    using Position = std::pair<int, int>;

    std::map<Position, T> &getGrid() {return _grid;}
    const std::map<Position, T> &getGrid()const {return _grid;}
    T &get(int i, int j) noexcept(false) {return _grid.at({i, j});}
    const T &get(int i, int j)const noexcept(false) {return _grid.at({i, j});}

    double getSurface(const OGRLineString &poly, int i, int j);

    friend OGRPoint operator*(double scal, const OGRPoint &p);
    friend OGRPoint operator*(OGRPoint &p, double scal);
    friend OGRPoint operator+(OGRPoint &p1, const OGRPoint &p2);

private:
    bool point_in_bbox(const OGRPoint &p, double x_min, double y_min, double x_max, double y_max);
    std::map<Position, T> _grid;    ///< the content of the grid, one element for each mesh with information
    OGRPoint _origin;               ///< its point of origin (with its attached spatial reference).
    double mesh_x_length;           ///< the width of each mesh (in _origin spatial reference units)
    double mesh_y_length;           ///< the height of each mesh (in _origin spatial reference units)
    int x_count;                    ///< the number of meshes on the x coordinate (from left to right)
    int y_count;                    ///< the number of meshes on the y coordinate (from bottom to top)
};

#endif // MESH_HPP

template<typename T>
double Mesh<T>::getSurface(const OGRLineString &poly, int i, int j) {
    // Compute mesh bounding box
    double x_min = i*mesh_x_length + _origin.getX();
    double x_max = (i+1)*mesh_x_length + _origin.getX();
    double y_min = j*mesh_y_length + _origin.getY();
    double y_max = (j+1)*mesh_y_length + _origin.getY();

    double surface = 0.0;
    bool has_intersect = false;
    std::vector<std::pair<double, double>> v_intersect;
    std::set<double> set_x;

    int pt_count = poly.getNumPoints();
    for (int i=0; i<pt_count; ++i) {
        OGRPoint p1, p2;
        poly.getPoint(i, &p1);
        poly.getPoint((i+1)%pt_count, &p2);
        auto equation = customToolbox::seg_equation(p1, p2);

        if (equation.first != std::numeric_limits<double>::infinity()) { // Case: y=ax+b, inc. a = 0
            //
        } else { // Case X=b
            //
        }
    }
    return surface;
}

OGRPoint operator*(double scal, const OGRPoint &p) {
    return OGRPoint{scal * p.getX(), scal * p.getY()};
}

OGRPoint operator*(const OGRPoint &p, double scal) {
    return OGRPoint{scal * p.getX(), scal * p.getY()};
}

OGRPoint operator+(const OGRPoint &p1, const OGRPoint &p2) {
    return OGRPoint{p1.getX()+p2.getX(), p1.getY()+p2.getY()};
}
