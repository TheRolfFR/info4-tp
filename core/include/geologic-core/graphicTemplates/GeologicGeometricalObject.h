/**
 * \file	GeologicGeometricalObject.h
 */

#ifndef GeologicGeometricalObject_H
#define GeologicGeometricalObject_H

//#include "geologic-core/objects/geo/untemporal/GeoPoint.h"
#include <ogr_geometry.h>
#include "geologic-core/utils/customToolbox.h"


class GeologicGeometricalObject {

    public:
        //*/ -------------------------------------------------
        GeologicGeometricalObject();
        virtual ~GeologicGeometricalObject();

        //*/ -------------------------------------------------
//        bool isPointWithinBounds(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP);
//        bool segmentContainsPoint(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP);
//        bool areSegmentsCrossing(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP, GeoPoint* pointQ);
//        bool areSegmentsStrictlyCrossing(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP, GeoPoint* pointQ);
//        bool areSegmentsOverlapping(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP, GeoPoint* pointQ);
//        GeoPoint* computeIntersection(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP, GeoPoint* pointQ);


//        bool isPointWithinBounds(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP);
//        bool segmentContainsPoint(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP);
//        bool areSegmentsCrossing(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP, OGRPoint* pointQ);
//        bool areSegmentsStrictlyCrossing(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP, OGRPoint* pointQ);
//        bool areSegmentsOverlapping(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP, OGRPoint* pointQ);
//        OGRPoint* computeIntersection(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP, OGRPoint* pointQ);


};

#endif // GeologicGeometricalObject_H
