/**
 * \file	TransportationTypeMap.cpp
 * \class   TransportationTypeMap
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of TransportationTypeMap object
 *
 * \details This class is a container for a map of TransportationType instances
 */

#include "geologic-core/core/geologic-mapper/transportation/TransportationTypeMap.h"


/**
 * \brief 	Default constructor of class TransportationTypeMap
 *
 * \param 	None
 * \return 	None
 */
TransportationTypeMap::TransportationTypeMap() {
    traTypMap = new std::unordered_map<std::string, TransportationType*>();
}

/**
 * \brief 	Default destructor of class TransportationTypeMap
 *
 * \param 	None
 * \return 	None
 */
TransportationTypeMap::~TransportationTypeMap() {
    std::unordered_map<std::string, TransportationType*>::iterator it = traTypMap->begin();
    for (; it!=traTypMap->end(); it++) delete(it->second);
    traTypMap->clear();
    delete(traTypMap);
    traTypMap = nullptr;
}
