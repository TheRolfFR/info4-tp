/**
 * \file	geoMetrics.cpp
 * \class	geoMetrics
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	03/09/2015
 * \brief	Main functions for managing geographical computations
 *
 * \details Contains several functions needed to manage geographical computations like distances, conversions, etc.
 */

#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"
#include <ogr_geometry.h>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Constants.hpp>
#include "geologic-core/core/geologic-mapper/GeologicMapper.h"
#include "geologic-core/utils/customToolbox.h"

//using namespace GeographicLib;
using namespace std;


namespace geoMetrics {

    /**
     * \brief 	Computes the distance between two OGRPoint
     *
     * \param 	pt1  Address of the first OGRPoint
     * \param 	pt2  Address of the second OGRPoint
     * \param 	dataRef  The Coordinate system of the two points (best if known)
     * \return 	The distance between the two points in meters
     *
     * The computation of the distance is different according to each CoordinateSystem. The CoordinateSystem is managed by the CoordinateSystemManager, and is called dataRef.
     * If expressed in WGS-84, the distance corresponds to a Haversine distance and is expressed in meters
     * If expressed in Lambert, Lambert II, Lambert II etendu, Lambert 93, the distance corresponds to an euclidean distance and is expressed in meters
     * Otherwise returns 0
     */
    double distanceTo(OGRPoint* pt1, OGRPoint* pt2, OGRSpatialReference* dataRef) {
        double dist = 0.0;

        unordered_map<OGRSpatialReference*, int>* cacheMap = CoordinateSystemManager::getInstance()->cooSysMapper->cacheCooSysMap;
        if (cacheMap->find(dataRef) == cacheMap->end())
            cacheMap->insert(pair<OGRSpatialReference*, int>(dataRef, dataRef->GetEPSGGeogCS()));

        //4807 => EPSG:27572 => lambert II etendu
        //4171 => EPSG:2154 => lambert 93
        int lambert [] = {4171, 4807};
        if (customToolbox::isIn(lambert, 2, cacheMap->at(dataRef))) {
            dist = (sqrt(pow((pt2->getX() - pt1->getX()), 2) + pow((pt2->getY() - pt1->getY()), 2)));
        } else if (cacheMap->at(dataRef) == 4326) { // //4807 => EPSG:4326 => WGS 84
            CoordinateSystemManager::getInstance()->geod->Inverse(pt1->getY(), pt1->getX(), pt2->getY(), pt2->getX(), dist);
        } else {
            dist = pt1->Distance(pt2);
        }
        return dist;
    }

    /**
     * \brief 	Computes the Haversine distance between two OGRPoint
     *
     * \param 	pt1  Address of the first OGRPoint
     * \param 	pt2  Address of the second OGRPoint
     * \return 	The Haversine distance between the two points in meters
     *
     * Expressed in WGS-84, the distance corresponds to a Haversine distance and is expressed in meters
     */
    double haversineDistanceTo(OGRPoint* pt1, OGRPoint* pt2) {
        double dist = 0.0;
        CoordinateSystemManager::getInstance()->geod->Inverse(pt1->getY(), pt1->getX(), pt2->getY(), pt2->getX(), dist);
        return dist;
    }

    /**
     * \brief 	Converts an OGRPoint with an input OGRSpatialReference to the OGRSpatialReference of the library
     *
     * \param 	point   The address of the point to convert
     * \param 	CSinput The address of the point's OGRSpatialReference
     * \return 	None
     */
    void convertToCurrentCS(OGRPoint* point, OGRSpatialReference *CSinput) {
        geoMetrics::convertTo(point, CSinput, CoordinateSystemManager::getInstance()->getDataRef());
    }

    /**
     * \brief 	Converts an OGRPoint with an input OGRSpatialReference to the OGRSpatialReference of the library
     *
     * \param 	point   The address of the point to convert
     * \param 	CSinput The address of the point's OGRSpatialReference
     * \return 	None
     */
    void convertGeometryToCurrentCS(OGRGeometry* geom, OGRSpatialReference *CSinput) {
        geoMetrics::convertGeometryTo(geom, CSinput, CoordinateSystemManager::getInstance()->getDataRef());
    }

    /**
     * \brief 	Converts an OGRPoint with an input OGRSpatialReference to and output OGRSpatialReference
     *
     * \param 	point       The address of the point to convert
     * \param 	CSinput     The address of the point's OGRSpatialReference
     * \param 	CSoutput    The address of the output OGRSpatialReference
     * \return 	None
     */
    void convertTo(OGRPoint* point, OGRSpatialReference* CSinput, OGRSpatialReference* CSoutput) {
        unordered_map<OGRSpatialReference*, int>* cacheMap = CoordinateSystemManager::getInstance()->cooSysMapper->cacheCooSysMap;
        if (cacheMap->find(CSinput) == cacheMap->end())
            cacheMap->insert(pair<OGRSpatialReference*, int>(CSinput, CSinput->GetEPSGGeogCS()));
        if (cacheMap->find(CSoutput) == cacheMap->end())
            cacheMap->insert(pair<OGRSpatialReference*, int>(CSoutput, CSoutput->GetEPSGGeogCS()));

        if (cacheMap->at(CSinput) == cacheMap->at(CSoutput)) return;

        OGRSpatialReference* cs_wgs84 = CoordinateSystemManager::getInstance()->getCSbyName("WGS 84");
        if (string(CSinput->GetAttrValue("GEOGCS")) == "OSM") {
            point->setX(geoMetrics::utm2lon(point->getX()));
            point->setY(geoMetrics::utm2lat(1.0 - point->getY()));
            geoMetrics::convertTo(point, cs_wgs84, CSoutput);
        } else if (string(CSoutput->GetAttrValue("GEOGCS")) == "OSM") {
            geoMetrics::convertTo(point, CSinput, cs_wgs84);
            point->setX(geoMetrics::long2utm(point->getX()));
            point->setY(geoMetrics::lat2utm(point->getY()));
        } else {
            string cooTraName = customToolbox::str(cacheMap->at(CSinput))+" to "+customToolbox::str(cacheMap->at(CSoutput));
            unordered_map<string, OGRCoordinateTransformation*>* transMap = CoordinateSystemManager::getInstance()->cooTraMapper->cooTraMap;
            if (transMap->find(cooTraName) == transMap->end()) {
                transMap->insert(pair<string, OGRCoordinateTransformation*>(cooTraName, OGRCreateCoordinateTransformation(CSinput, CSoutput)));
            }
            OGRCoordinateTransformation* transOp = transMap->at(cooTraName);
            double x = point->getX();
            double y = point->getY();
            if (transOp->Transform(1, &x, &y)) {
                point->setX(x);
                point->setY(y);
            } else {

            }
        }
    }

    /**
     * \brief 	Converts an OGRPoint with an input OGRSpatialReference to and output OGRSpatialReference
     *
     * \param 	point       The address of the point to convert
     * \param 	CSinput     The address of the point's OGRSpatialReference
     * \param 	CSoutput    The address of the output OGRSpatialReference
     * \return 	None
     */
    void convertTo(double& ptx, double& pty, OGRSpatialReference* CSinput, OGRSpatialReference* CSoutput) {
        unordered_map<OGRSpatialReference*, int>* cacheMap = CoordinateSystemManager::getInstance()->cooSysMapper->cacheCooSysMap;
        if (cacheMap->find(CSinput) == cacheMap->end())
            cacheMap->insert(pair<OGRSpatialReference*, int>(CSinput, CSinput->GetEPSGGeogCS()));
        if (cacheMap->find(CSoutput) == cacheMap->end())
            cacheMap->insert(pair<OGRSpatialReference*, int>(CSoutput, CSoutput->GetEPSGGeogCS()));

        if (cacheMap->at(CSinput) == cacheMap->at(CSoutput)) return;

        OGRSpatialReference* cs_wgs84 = CoordinateSystemManager::getInstance()->getCSbyName("WGS 84");
        if (string(CSinput->GetAttrValue("GEOGCS")) == "OSM") {
            ptx = geoMetrics::utm2lon(ptx);
            pty = geoMetrics::utm2lat(1.0 - pty);
            geoMetrics::convertTo(ptx, pty, cs_wgs84, CSoutput);
        } else if (string(CSoutput->GetAttrValue("GEOGCS")) == "OSM") {
            geoMetrics::convertTo(ptx, pty, CSinput, cs_wgs84);
            ptx = geoMetrics::long2utm(ptx);
            pty = geoMetrics::lat2utm(pty);
        } else {
            string cooTraName = customToolbox::str(cacheMap->at(CSinput))+" to "+customToolbox::str(cacheMap->at(CSoutput));
            unordered_map<string, OGRCoordinateTransformation*>* transMap = CoordinateSystemManager::getInstance()->cooTraMapper->cooTraMap;
            if (transMap->find(cooTraName) == transMap->end()) {
                transMap->insert(pair<string, OGRCoordinateTransformation*>(cooTraName, OGRCreateCoordinateTransformation(CSinput, CSoutput)));
            }
            OGRCoordinateTransformation* transOp = transMap->at(cooTraName);
            transOp->Transform(1, &ptx, &pty);
        }
    }

    /**
     * \brief 	Converts an OGRPoint with an input OGRSpatialReference to and output OGRSpatialReference
     *
     * \param 	point       The address of the point to convert
     * \param 	CSinput     The address of the point's OGRSpatialReference
     * \param 	CSoutput    The address of the output OGRSpatialReference
     * \return 	None
     */
    void convertGeometryTo(OGRGeometry* geom, OGRSpatialReference* CSinput, OGRSpatialReference* CSoutput) {
        unordered_map<OGRSpatialReference*, int>* cacheMap = CoordinateSystemManager::getInstance()->cooSysMapper->cacheCooSysMap;
        if (cacheMap->find(CSinput) == cacheMap->end())
            cacheMap->insert(pair<OGRSpatialReference*, int>(CSinput, CSinput->GetEPSGGeogCS()));
        if (cacheMap->find(CSoutput) == cacheMap->end())
            cacheMap->insert(pair<OGRSpatialReference*, int>(CSoutput, CSoutput->GetEPSGGeogCS()));

        if (cacheMap->at(CSinput) == cacheMap->at(CSoutput)) return;
        geom->assignSpatialReference(CSinput);
        geom->transformTo(CSoutput);


//        string cooTraName = customToolbox::str(cacheMap->at(CSinput))+" to "+customToolbox::str(cacheMap->at(CSoutput));
//        unordered_map<string, OGRCoordinateTransformation*>* transMap = CoordinateSystemManager::getInstance()->cooTraMapper->cooTraMap;
//        if (transMap->find(cooTraName) == transMap->end()) {
//            transMap->insert(pair<string, OGRCoordinateTransformation*>(cooTraName, OGRCreateCoordinateTransformation(CSinput, CSoutput)));
//        }
//        OGRCoordinateTransformation* transOp = transMap->at(cooTraName);


//        double x = point->getX();
//        double y = point->getY();
//        if (transOp->Transform(1, &x, &y)) {
//            point->setX(x);
//            point->setY(y);
//        }
    }

    /**
     * \brief conversion from WGS84 longitude to [0,1.0] pseudo UTM value
     *
     * \param lon WGS84 longitude in degree
     * \return pseudo UTM value between 0 (180.0 °W) to 1.0 (180.0 °E)
     */
    double long2utm(double lon) {
        return (lon+180.0)/360.0;
    }

    /**
     * \brief conversion from WGS84 latitude to [0,1.0] pseudo UTM value
     *
     * \param lat WGS84 latitude in degree
     * \return pseudo UTM value between 0 (i.e. 85.0511 °N) to 1.0 (i.e. 85.0511 °S)
     */
    double lat2utm(double lat) {
        return (1.0 - log(tan(lat*M_PI/180.0) + 1.0/cos(lat*M_PI/180.0))/ M_PI)/2.0;
    }

    /**
     * \brief conversion from pseudo UTM x value to WGS84 longitude
     *
     * \param utm_x pseudo UTM x value
     * \return WGS84 longitude value in degree
     */
    double utm2lon(double utm_x) {
        return utm_x*360.0 - 180.0;
    }

    /**
     * \brief conversion from pseudo UTM y value to WGS84 latitude
     *
     * \param utm_y pseudo UTM y value
     * \return WGS84 latitude value in degree
     */
    double utm2lat(double utm_y) {
        double lat = atan(sinh(M_PI*(1.0 - 2.0*utm_y)));
        return lat*180.0/M_PI;
    }

    /**
     * \brief conversion from WGS84 longitude to tile x index
     *
     * \param lon WGS84 longitude in degree
     * \param z zoom level (0 to 18)
     * \return x index of the bounding tile
     */
    int long2tilex(double lon, int z) {
        return (int) (floor((lon + 180.0) / 360.0*pow(2.0, z)));
    }

    /**
     * \brief conversion from WGS84 latitude to tile y index
     *
     * \param lat WGS84 latitude in degree
     * \param z zoom level (0 to 18)
     * \return y index of the bounding tile
     */
    int lat2tiley(double lat, int z) {
        return (int) (floor((1.0 - log(tan(lat*M_PI/180.0) + 1.0/cos(lat*M_PI/180.0))/M_PI)/2.0*pow(2.0, z)));
    }

    /**
     * \brief utm2tile computes tile index based on its pseudo UTM coordinates
     *
     * \param utm pseudo UTM
     * \param zoom, the zoom level
     * \return index
     */
    int utm2tile(double utm, int zoom) {
        return (int) floor(pow(2.0, zoom)*utm);
    }

    /**
     * \brief tile2utm converts from tile index to pseudo UTM coordinates
     *
     * \param idx the tile index
     * \param zoom the zoom level
     * \return the pseudo UTM coordinate
     */
    double tile2utm(int idx, int zoom) {
        return (double) idx/pow(2.0, zoom);
    }

    /*!
     * \brief OsmToWgs84 converts normalized pseudo UTM to WGS84 coordinates
     * \param x the [0..1] longitude (from left to right)
     * \param y the [0..1] latitude (from top to bottom)
     */
    tuple<double, double> OsmToWgs84(double x, double y) {
        return make_tuple(geoMetrics::utm2lon(x), geoMetrics::utm2lat(y));
    }

    /*!
     * \brief conversion from WGS84 coordinates to [0,1.0]^2 pseudo UTM value
     * \param p WGS84 location (degree)
     * \return pseudo UTM value
     */
    tuple<double, double> wgs84ToOsm(double lon, double lat) {
        return make_tuple(geoMetrics::long2utm(lon), geoMetrics::lat2utm(lat));
    }

    /*!
     * \brief conversion from WGS84 coordinates to [0,1.0]^2 pseudo UTM value
     * \param p WGS84 location (degree)
     * \return pseudo UTM value
     */
    tuple<double, double> wgs84ToOsm(OGRPoint* p) {
        return geoMetrics::wgs84ToOsm(p->getX(), p->getY());
    }

    /**
     * \brief 	Converts an OGRPoint with an input OGRSpatialReference to and output OGRSpatialReference
     *
     * \param 	point       The address of the point to convert
     * \param 	CSinput     The address of the point's OGRSpatialReference
     * \param 	CSoutput    The address of the output OGRSpatialReference
     * \return 	None
     */
    pair<double, double> seg_equation(OGRPoint* pt1, OGRPoint* pt2) {
        double a = (pt2->getY() - pt1->getY()) / (pt2->getX() - pt1->getX());
        double b = pt1->getY() - a*pt1->getX();
        return {a, b};
    }
}
