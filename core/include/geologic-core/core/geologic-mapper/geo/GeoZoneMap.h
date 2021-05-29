/**
 * \file	GeoZoneMap.h
 */

#ifndef GEOZONEMAP_H
#define GEOZONEMAP_H

#include <string>
#include <unordered_map>
#include "geologic-core/objects/geo/untemporal/GeoZone.h"


class GeoZoneMap {

    public:
        //*/ -------------------------------------------------
        GeoZoneMap();
        virtual ~GeoZoneMap();

        //*/ -------------------------------------------------
        std::unordered_map<std::string, GeoZone*>* geoZonMap;
};

#endif // GEOZONEMAP_H