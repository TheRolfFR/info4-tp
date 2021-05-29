#include <Common/triangle.h>
#include <algorithm>

using namespace std;

Triangle &Triangle::operator=(const OGRPolygon &points) {
    int count = min(points.getExteriorRing()->getNumPoints(), 3);
    for (int i=0; i<count; ++i) {
        OGRPoint p;
        points.getExteriorRing()->getPoint(i, &p);
        xs[i] = p.getX();
        ys[i] = p.getY();
        zs[i] = p.getZ();
    }
    return *this;
}

Triangle::Triangle() {}

Triangle::Triangle(const OGRPolygon &points) {
    *this = points;
}
