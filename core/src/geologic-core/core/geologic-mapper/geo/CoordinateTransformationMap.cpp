/**
 * \file	CoordinateTransformationMap.cpp
 * \class   CoordinateTransformationMap
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of CoordinateTransformationMap object
 *
 * \details This class is a container for a map of OGRCoordinateTransformation instances
 */

#include "geologic-core/core/geologic-mapper/geo/CoordinateTransformationMap.h"


/**
 * \brief 	Default constructor of class CoordinateTransformationMap
 *
 * \param 	None
 * \return 	None
 */
CoordinateTransformationMap::CoordinateTransformationMap() {
    cooTraMap = new std::unordered_map<std::string, OGRCoordinateTransformation*>();
}

/**
 * \brief 	Default destructor of class CoordinateTransformationMap
 *
 * \param 	None
 * \return 	None
 */
CoordinateTransformationMap::~CoordinateTransformationMap() {
    std::unordered_map<std::string, OGRCoordinateTransformation*>::iterator it = cooTraMap->begin();
    for (; it!=cooTraMap->end(); it++) delete(it->second);
    cooTraMap->clear();
    delete(cooTraMap);
    cooTraMap = nullptr;
}
