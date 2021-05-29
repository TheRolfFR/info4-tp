/**
 * \file	GeoZoneMap.cpp
 * \class   GeoZoneMap
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of GeoZoneMap object
 *
 * \details This class is a container for a map of GeoZone instances
 */

#include "geologic-core/core/geologic-mapper/geo/GeoZoneMap.h"


/**
 * \brief 	Default constructor of class GeoZoneMap
 *
 * \param 	None
 * \return 	None
 */
GeoZoneMap::GeoZoneMap() {
    geoZonMap = new std::unordered_map<std::string, GeoZone*>();
}

/**
 * \brief 	Default destructor of class GeoZoneMap
 *
 * \param 	None
 * \return 	None
 */
GeoZoneMap::~GeoZoneMap() {
    std::unordered_map<std::string, GeoZone*>::iterator it = geoZonMap->begin();
    for (; it!=geoZonMap->end(); it++) delete(it->second);
    geoZonMap->clear();
    delete(geoZonMap);
    geoZonMap = nullptr;
}