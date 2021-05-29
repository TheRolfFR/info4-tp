/**
 * \file	TemporalGeoZone.h
 */

#ifndef TEMPORALGEOZONE_H
#define TEMPORALGEOZONE_H

#include "geologic-core/objects/geo/temporal/TemporalGeoData.h"
#include "geologic-core/objects/geo/untemporal/GeoZone.h"


class TemporalGeoZone : public TemporalGeoData {

    public:
        //*/ -------------------------------------------------
        TemporalGeoZone();
        virtual ~TemporalGeoZone();

        TemporalGeoZone(GeoZone* zone, time_t timestamp);

        //*/ -------------------------------------------------
        GeoZone* zone;
};

#endif // TEMPORALGEOZONE_H
