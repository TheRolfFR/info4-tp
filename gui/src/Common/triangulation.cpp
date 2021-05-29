#include <Common/triangulation.h>
#include <cmath>
#include <QVector3D>

using namespace std;

bool counterClockwise(QVector3D a, QVector3D b, QVector3D c) {
    QVector3D dir = QVector3D::crossProduct(b-a, c-a);
    dir.normalize();
    return dir.z() <= 0;
}

bool containsPoint(QVector3D a, QVector3D b, QVector3D c, QVector3D d) {
    auto v0 = c - a;
    auto v1 = b - a;
    auto v2 = d - a;

    auto dot00 = QVector3D::dotProduct(v0, v0);
    auto dot01 = QVector3D::dotProduct(v0, v1);
    auto dot02 = QVector3D::dotProduct(v0, v2);
    auto dot11 = QVector3D::dotProduct(v1, v1);
    auto dot12 = QVector3D::dotProduct(v1, v2);

    auto invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    auto u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    auto v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}

/*!
 * \brief Triangulation::triangulate_ear triangulates a set of polygons in order to be able to texture/paint it
 * \param polygons the previously converted to viewref set of polygons, as an OGRMultiPolygon pointer
 * \return
 */
vector<float> Triangulation::triangulate_ear(OGRMultiPolygon *polygons) {
    vector<float> vertices;


    if (!polygons)
        return vertices;

    for (OGRPolygon *polygon: polygons) {
        std::vector<QVector3D> tmp_vertices;

        OGRLinearRing *ext_ring = polygon->getExteriorRing()->clone()->toLinearRing();
        if (!ext_ring)
            continue;
        if (ext_ring->isClockwise())
            ext_ring->reverseWindingOrder();
        for (OGRPoint &pt: ext_ring) {
            QVector3D point{(float) pt.getX(), (float) pt.getY(), 0.0f};
            if(find(tmp_vertices.begin(), tmp_vertices.end(), point) == tmp_vertices.end()) {
                tmp_vertices.push_back(point);
            }
        }

        unsigned int a = 0, b = 1, c = 2;
        unsigned int last_size = tmp_vertices.size();
        unsigned int size_unchanged = 0;

        while(tmp_vertices.size() > 2) {
            bool triangle_found = true;
            if(counterClockwise(tmp_vertices[a], tmp_vertices[b], tmp_vertices[c])) {
                triangle_found = false;
            } else {
                unsigned int i = 0;
                for(auto& p: tmp_vertices) {
                    if(a != i && b != i && c != i && containsPoint(tmp_vertices[a], tmp_vertices[b], tmp_vertices[c], p)) {
                        triangle_found = false;
                        break;
                    }
                    i++;
                }
            }
            if(triangle_found) {
                vertices.push_back(tmp_vertices[a].x());
                vertices.push_back(tmp_vertices[a].y());
                vertices.push_back(tmp_vertices[a].z());

                vertices.push_back(tmp_vertices[b].x());
                vertices.push_back(tmp_vertices[b].y());
                vertices.push_back(tmp_vertices[b].z());

                vertices.push_back(tmp_vertices[c].x());
                vertices.push_back(tmp_vertices[c].y());
                vertices.push_back(tmp_vertices[c].z());

                tmp_vertices.erase(tmp_vertices.begin()+b);
            } else {
                a++;
            }
            a %= tmp_vertices.size();
            b = a + 1;
            c = a + 2;
            b %= tmp_vertices.size();
            c %= tmp_vertices.size();

            if(last_size == tmp_vertices.size()) {
                size_unchanged++;
            } else {
                size_unchanged = 0;
            }
            last_size = tmp_vertices.size();
            if(size_unchanged > tmp_vertices.size() * 2) {
                break;
            }
        }
    }

    return vertices;
}

