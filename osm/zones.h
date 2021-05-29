#ifndef ZONES_H
#define ZONES_H

#include <osmloader.h>
#include <ogr_geometry.h>
#include <ogr_spatialref.h>
#include <vector>
#include <Common/triangle.h>
#include <Data/data.h>
#include <string>
#include <memory>
#include <QtOpenGL/QtOpenGL>

class Zones {
    OGRMultiPolygon _zones_polygons;
    OGRMultiLineString zones_boundaries;
    OGRSpatialReference geo_ref;
    OGRSpatialReference *_viewref;

public:
    Zones();

    /*!
     * \brief load loads an osm file with relations, way and nodes defining administrative zones
     * Goes through relations, finds ways of the outer bound, assembles them.
     * \param filename
     */
    void load(const char *filename);
    const OGRMultiLineString &getBoundaries() const {return zones_boundaries;}
    const OGRMultiPolygon &getPolygons() const {return _zones_polygons;}
    const OGRSpatialReference &getGeoRef() {return geo_ref;}
    OGRMultiLineString *getBoundariesPtr() {return &zones_boundaries;}
    OGRMultiPolygon *getPolygonsPtr() {return &_zones_polygons;}
    OGRSpatialReference *getGeoRefPtr() {return &geo_ref;}
    OGRSpatialReference *getViewref() const;
    void setViewref(OGRSpatialReference *viewref);
};

#endif // ZONES_H
