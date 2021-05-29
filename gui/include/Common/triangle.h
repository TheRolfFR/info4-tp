#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>
#include <ogr_geometry.h>

struct Triangle {
    std::array<double, 3> xs;
    std::array<double, 3> ys;
    std::array<double, 3> zs;

    Triangle &operator=(const OGRPolygon &points);

    Triangle();
    Triangle(const OGRPolygon &points);
    Triangle(const Triangle &other) = default;
    Triangle(Triangle &&other) = default;
    Triangle &operator=(const Triangle &other) = default;
    Triangle &operator=(Triangle &&other) = default;
    ~Triangle() = default;
};

#endif // TRIANGLE_H
