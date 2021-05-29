/**
 * \file	IndividualMap.cpp
 * \class   IndividualMap
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of IndividualMap object
 *
 * \details This class is a container for a map of Individual instances
 */

#include "geologic-core/core/geologic-mapper/social/IndividualMap.h"


/**
 * \brief 	Default constructor of class IndividualMap
 *
 * \param 	None
 * \return 	None
 */
IndividualMap::IndividualMap() {
   indMap = new std::unordered_map<std::string, Individual*>();
}

/**
 * \brief 	Default destructor of class IndividualMap
 *
 * \param 	None
 * \return 	None
 */
IndividualMap::~IndividualMap() {
    std::unordered_map<std::string, Individual*>::iterator it = indMap->begin();
    for (; it!=indMap->end(); it++) delete(it->second);
    indMap->clear();
    delete(indMap);
    indMap = nullptr;
}

