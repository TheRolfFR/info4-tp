/**
 * \file	TemporalGeoPoint.h
 */

#ifndef TEMPORALGEOPOINT_H
#define TEMPORALGEOPOINT_H

#include "geologic-core/objects/geo/temporal/TemporalGeoData.h"
#include "geologic-core/objects/geo/untemporal/GeographicalObject.h"
#include <ogr_geometry.h>


class TemporalGeoPoint : public TemporalGeoData, public GeographicalObject {

    public:
        //*/ -------------------------------------------------
        TemporalGeoPoint();
        virtual ~TemporalGeoPoint();

        TemporalGeoPoint(double timestamp);
        TemporalGeoPoint(double x, double y, double z, double timestamp);
        TemporalGeoPoint(OGRPoint* point, double timestamp);
        TemporalGeoPoint(TemporalGeoPoint* point);
};

#endif // TEMPORALGEOPOINT_H
