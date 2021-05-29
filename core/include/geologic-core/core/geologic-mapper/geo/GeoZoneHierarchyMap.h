/**
 * \file	GeoZoneHierarchyMap.h
 */

#ifndef GEOZONEHIERARCHYMAP_H
#define GEOZONEHIERARCHYMAP_H

#include <string>
#include <unordered_map>
#include "geologic-core/core/geologic-mapper/geo/GeoZoneMap.h"


class GeoZoneHierarchyMap {

    public:
        //*/ -------------------------------------------------
        GeoZoneHierarchyMap();
        virtual ~GeoZoneHierarchyMap();

        //*/ -------------------------------------------------
        std::unordered_map<std::string, std::unordered_map<std::string, GeoZone*>*>* geoZonHieMap;
};

#endif // GEOZONEHIERARCHYMAP_H