#ifndef OGR_POINT_OBJECT_H
#define OGR_POINT_OBJECT_H

#include <Object/childobject.h>
#include <gdal/ogr_geometry.h>
#include <Data/data.h>
#include <Material/material.h>

/*!
 * \brief The ogr_point_object class manages OGRPoint, OGRMultiPoint, and OGRLineString static objects
 */
class ogr_point_object : public ChildObject {
public:
    ogr_point_object(std::shared_ptr<Data> ogr_pt_data, std::shared_ptr<Material> ogr_pt_mat, View *v);
    ~ogr_point_object() {}
};

#endif // OGR_POINT_OBJECT_H
