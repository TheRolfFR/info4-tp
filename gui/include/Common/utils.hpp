#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <ogr_geometry.h>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (const T& e: v) {
        os << e << " ";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const OGRPoint &p) {
    os << "(" << p.getX() << ", " << p.getY() << ")";
    return os;
}

#endif // UTILS_HPP
