/**
 * \file	CoordinateSystemMap.h
 */

#ifndef COORDINATESYSTEMMAP_H
#define COORDINATESYSTEMMAP_H

#include <string>
#include <unordered_map>
#include <ogr_spatialref.h>
#include <ogr_geometry.h>
#include <memory>


class CoordinateSystemMap {

    public:
        //*/ -------------------------------------------------
        CoordinateSystemMap();
        virtual ~CoordinateSystemMap();

        //*/ -------------------------------------------------
        std::unordered_map<std::string, std::shared_ptr<OGRSpatialReference>>* cooSysMap;
        std::unordered_map<OGRSpatialReference*, int>* cacheCooSysMap;

};

#endif // COORDINATESYSTEMMAP_H
