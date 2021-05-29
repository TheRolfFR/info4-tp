#ifndef OGR_POINT_DATA_H
#define OGR_POINT_DATA_H

#include <Data/uniquedata.h>
#include <gdal/ogr_geometry.h>

/*!
 * \brief The ogr_point_data class handles one OGRPoint data conversion and loading into GPU
 */
class ogr_point_data : public UniqueData {
    OGRPoint _my_point;
public:
    ogr_point_data(const OGRPoint &pt);
    virtual ~ogr_point_data() {};
};

/*!
 * \brief The ogr_multipoint_data class converts and loads an OGRMultipoint instance into the GPU
 */
class ogr_multipoint_data: public UniqueData {
    OGRMultiPoint _multipoints;
public:
    ogr_multipoint_data(const OGRMultiPoint &pts);
    virtual ~ogr_multipoint_data() {}
};

/*!
 * \brief The ogr_linestring_data class converts and loads an OGRLineString instance into the GPU
 */
class ogr_linestring_data: public UniqueData {
public:
    ogr_linestring_data(OGRLineString *linestring=nullptr);
    virtual ~ogr_linestring_data() {}
};

/*!
 * \brief The ogr_multilinestring_data class converts and loads an OGRLineString instance into the GPU
 */
class ogr_multilinestring_data: public UniqueData {
    std::vector<GLsizei> m_indices_sizes;
    std::vector<GLvoid *> m_indices_offsets;
public:
    ogr_multilinestring_data(OGRMultiLineString *multi);
    virtual ~ogr_multilinestring_data() {}
    virtual void draw() override;
};

class ogr_multipolygon_data: public UniqueData {
public:
    ogr_multipolygon_data(OGRMultiPolygon *polygons=nullptr);
    virtual ~ogr_multipolygon_data() {}
};

#endif // OGR_POINT_DATA_H
