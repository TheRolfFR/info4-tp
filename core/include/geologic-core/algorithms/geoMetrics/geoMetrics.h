/**
 * \file	geoMetrics.h
 */

#ifndef GEOMETRICS_H
#define GEOMETRICS_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <ogr_geometry.h>
#include "geologic-core/core/geologic-launcher/CoordinateSystemManager.h"

class OGRPoint;


namespace geoMetrics {

    //double distanceTo(OGRPoint* pt1, OGRPoint* pt2);
    double distanceTo(OGRPoint* pt1, OGRPoint* pt2, OGRSpatialReference* dataRef=CoordinateSystemManager::getInstance()->getDataRef());
    double haversineDistanceTo(OGRPoint* pt1, OGRPoint* pt2);
    void convertToCurrentCS(OGRPoint* point, OGRSpatialReference *CSinput);
    void convertGeometryToCurrentCS(OGRGeometry* geom, OGRSpatialReference *CSinput);
    void convertTo(OGRPoint* point, OGRSpatialReference *CSinput, OGRSpatialReference *CSoutput);
    void convertTo(double& ptx, double& pty, OGRSpatialReference *CSinput, OGRSpatialReference *CSoutput);
    void convertGeometryTo(OGRGeometry* geom, OGRSpatialReference *CSinput, OGRSpatialReference *CSoutput);

    double long2utm(double lon);
    double lat2utm(double lat);
    double utm2lon(double utm_x);
    double utm2lat(double utm_y);
    int long2tilex(double lon, int z);
    int lat2tiley(double lat, int z);
    int utm2tile(double utm, int zoom);
    double tile2utm(int idx, int zoom);
    std::tuple<double, double> OsmToWgs84(double x, double y);
    std::tuple<double, double> wgs84ToOsm(double lon, double lat);
    std::tuple<double, double> wgs84ToOsm(OGRPoint* p);
    std::pair<double, double> seg_equation(OGRPoint* pt1, OGRPoint* pt2);
}
//#include "geologic-core/utils/customToolbox_impl.h"
#endif // GEOMETRICS_H
