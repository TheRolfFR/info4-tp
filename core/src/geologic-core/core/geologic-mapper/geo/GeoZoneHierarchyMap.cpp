/**
 * \file	GeoZoneHierarchyMap.cpp
 * \class   GeoZoneHierarchyMap
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of GeoZoneHierarchyMap object
 *
 * \details This class is a container for a map of map of GeoZone instances. Commonly used to differentiate the several levels of GeoZone over a territory
 */

#include "geologic-core/core/geologic-mapper/geo/GeoZoneHierarchyMap.h"


/**
 * \brief 	Default constructor of class GeoZoneHierarchyMap
 *
 * \param 	None
 * \return 	None
 */
GeoZoneHierarchyMap::GeoZoneHierarchyMap() {
    geoZonHieMap = new std::unordered_map<std::string, std::unordered_map<std::string, GeoZone*>*>();
}

/**
 * \brief 	Default destructor of class GeoZoneHierarchyMap
 *
 * \param 	None
 * \return 	None
 */
GeoZoneHierarchyMap::~GeoZoneHierarchyMap() {
    std::unordered_map<std::string, std::unordered_map<std::string, GeoZone*>*>::iterator it = geoZonHieMap->begin();
    for (; it!=geoZonHieMap->end(); it++) delete(it->second);
    geoZonHieMap->clear();
    delete(geoZonHieMap);
    geoZonHieMap = nullptr;
}