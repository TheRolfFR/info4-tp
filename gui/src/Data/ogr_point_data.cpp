#include <Data/ogr_point_data.h>
#include <geologic-core/core/geologic-launcher/CoordinateSystemManager.h>
#include <Common/triangulation.h>
#include <exception>
#include <iostream>

using namespace std;

ogr_point_data::ogr_point_data(const OGRPoint &pt): UniqueData("OGRPoint") {
    _my_point = pt;
    OGRSpatialReference wgs84;
    wgs84.importFromEPSG(4326);
    CoordinateSystemManager *csm = CoordinateSystemManager::getInstance();
    if (csm) {
        auto view_ref = csm->getViewRef();
        if (view_ref) {
            OGRCoordinateTransformation *t = OGRCreateCoordinateTransformation(&wgs84, view_ref);
            if (t) {
                _my_point.transform(t);
                OCTDestroyCoordinateTransformation(t);
                vector<float> vertices{
                    static_cast<float>(_my_point.getX()),
                    static_cast<float>(_my_point.getY()),
                    static_cast<float>(_my_point.getZ())
                };
                setVertices(vertices);
                setStructureType(GL_POINTS);
            }
        }
    }
}

ogr_multipoint_data::ogr_multipoint_data(const OGRMultiPoint &pts): UniqueData("OGRMultiPoint") {
    _multipoints = pts; // See if change to pointer or de-const pts to modify.
    OGRSpatialReference wgs84;
    wgs84.importFromEPSG(4326);
    CoordinateSystemManager *csm = CoordinateSystemManager::getInstance();
    if (csm) {
        auto view_ref = csm->getViewRef();
        if (view_ref) {
            OGRCoordinateTransformation *t = OGRCreateCoordinateTransformation(&wgs84, view_ref);
            if (t) {
                _multipoints.transform(t);
                OCTDestroyCoordinateTransformation(t);
                vector<float> vertices;
                for (const OGRPoint *p: _multipoints) {
                    vertices.push_back(p->getX());
                    vertices.push_back(p->getY());
                    vertices.push_back(p->getZ());
                }
                setVertices(vertices);
                setStructureType(GL_POINTS);
            }
        }
    }
}

/*!
 * \brief ogr_linestring_data::ogr_linestring_data constructor
 * \param linestring a non owner pointer to the line string that shall be loaded
 */
ogr_linestring_data::ogr_linestring_data(OGRLineString *linestring): UniqueData("OGRLineString") {
    if (linestring) {
        OGRSpatialReference wgs84;
        wgs84.importFromEPSG(4326);
        CoordinateSystemManager *csm = CoordinateSystemManager::getInstance();
        if (csm) {
            auto view_ref = csm->getViewRef();
            if (view_ref) {
                OGRCoordinateTransformation *t = OGRCreateCoordinateTransformation(&wgs84, view_ref);
                if (t) {
                    vector<double> Xs; Xs.resize(linestring->getNumPoints());
                    vector<double> Ys; Ys.resize(linestring->getNumPoints());
                    vector<double> Zs; Zs.resize(linestring->getNumPoints());
                    linestring->getPoints(&Xs[0], sizeof(double), &Ys[0], sizeof(double), &Zs[0], sizeof(double));
                    t->Transform(Xs.size(), &Xs[0], &Ys[0], &Zs[0]);
                    OCTDestroyCoordinateTransformation(t);
                    vector<float> vertices;
                    for (size_t i=0; i<Xs.size(); ++i) {
                        vertices.push_back(Xs[i]);
                        vertices.push_back(Ys[i]);
                        vertices.push_back(Zs[i]);
                    }
                    setVertices(vertices);
                    setStructureType(GL_LINE_STRIP);
                }
            }
        }
    }
}

/*!
 * \brief ogr_multilinestring_data::ogr_multilinestring_data constructor
 * \param multi a non owner pointer to the OGRMultiLineString to be converted and loaded.
 *
 * This constructor converts the coordinates to the viewref projection. For drawing with one draw call, il resorts on glMultiDrawElements,
 * hence the computation of indices offsets and cumulation for transmitting the multiple shapes to the GPU.
 */
ogr_multilinestring_data::ogr_multilinestring_data(OGRMultiLineString *multi): UniqueData("OGRMultiLineString") {
    OGRSpatialReference wgs84;
    wgs84.importFromEPSG(4326);
    CoordinateSystemManager *csm = CoordinateSystemManager::getInstance();
    vector<float> vertices;
    vector<unsigned int> indices;
    if (multi && csm) {
        auto view_ref = csm->getViewRef();
        if (view_ref) {
            OGRCoordinateTransformation *t = OGRCreateCoordinateTransformation(&wgs84, view_ref);
            if (t) {
                for (OGRLineString *line: multi) {
                    vector<double> Xs, Ys, Zs;
                    Xs.resize(line->getNumPoints());
                    Ys.resize(line->getNumPoints());
                    Zs.resize(line->getNumPoints());
                    line->getPoints(&Xs[0], sizeof(double), &Ys[0], sizeof(double), &Zs[0], sizeof(double));
                    t->Transform(Xs.size(), &Xs[0], &Ys[0], &Zs[0]);
                    for (size_t i=0; i<Xs.size(); ++i) {
                        vertices.push_back(Xs[i]);
                        vertices.push_back(Ys[i]);
                        vertices.push_back(Zs[i]);
//                        cout << "Push (" << Xs[i] << " " << Ys[i] << " " << Zs[i] << ")" << endl;
                        indices.push_back((vertices.size()/3)-1);
//                        cout << "Push (indices) " << indices.back() << endl;
                    }
                    m_indices_sizes.push_back(Xs.size());
//                    cout << "Points count in current shape " << m_indices_sizes.back() << endl;
                }
                unsigned int cumulated_indices = 0;
                for (unsigned int v: m_indices_sizes) {
                    m_indices_offsets.push_back(BUFFER_OFFSET(cumulated_indices * sizeof(GLuint)));
//                    cout << "Offset: " << m_indices_offsets.back() << endl;
                    cumulated_indices += v;
                }
                setVertices(vertices);
                setIndices(indices);
                setStructureType(GL_LINE_STRIP);
            }
        }
    }
}

/*!
 * \brief ogr_multilinestring_data::draw overrides UniqueData::draw to use only one draw call to several LINE_STRIPs
 */
void ogr_multilinestring_data::draw() {
    if(m_loaded) {
        bind();
        glMultiDrawElements(m_structureType, m_indices_sizes.data(), GL_UNSIGNED_INT, m_indices_offsets.data(), m_indices_offsets.size());
        glBindVertexArray(0);
    }
}


ogr_multipolygon_data::ogr_multipolygon_data(OGRMultiPolygon *polygons): UniqueData("OGRMultiPolygon") {
    OGRSpatialReference wgs84;
    wgs84.importFromEPSG(4326);
    CoordinateSystemManager *csm = CoordinateSystemManager::getInstance();
    if (polygons && csm) {
        auto view_ref = csm->getViewRef();
        if (view_ref) {
            OGRCoordinateTransformation *t = OGRCreateCoordinateTransformation(&wgs84, view_ref);
            if (t) {
                polygons->transform(t);
                vector<float> vertices = Triangulation::triangulate_ear(polygons);
                setVertices(vertices);
                setStructureType(GL_TRIANGLES);
            }
        }
    }
}
