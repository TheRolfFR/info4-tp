/**
 * \file	CoordinateSystemMap.cpp
 * \class   CoordinateSystemMap
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of CoordinateSystemMap object
 *
 * \details This class is a container for a map of OGRSpatialReference instances
 */

#include "geologic-core/core/geologic-mapper/geo/CoordinateSystemMap.h"


/**
 * \brief 	Default constructor of class CoordinateSystemMap
 *
 * \param 	None
 * \return 	None
 */
CoordinateSystemMap::CoordinateSystemMap() {
    cooSysMap = new std::unordered_map<std::string, std::shared_ptr<OGRSpatialReference>>();
    cacheCooSysMap = new std::unordered_map<OGRSpatialReference*, int>();
}

/**
 * \brief 	Default destructor of class CoordinateSystemMap
 *
 * \param 	None
 * \return 	None
 */
CoordinateSystemMap::~CoordinateSystemMap() {
    cooSysMap->clear();
    delete(cooSysMap);
    cooSysMap = nullptr;

    cacheCooSysMap->clear();
    delete(cacheCooSysMap);
    cacheCooSysMap = nullptr;
}
