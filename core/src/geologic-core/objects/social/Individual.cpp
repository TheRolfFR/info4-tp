/**
 * \file	Individual.cpp
 * \class	Individual
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Individual object
 *
 * \details Methods of Individual object. Inherits from MobileObject
 * An Individual object represents an Individual...
 */

#include "geologic-core/objects/social/Individual.h"

using namespace std;


/**
 * \brief 	Default constructor of class Individual
 *
 * \param 	None
 * \return 	None
 */
Individual::Individual(std::string Identity) {
    this->Identity = Identity;
    this->IMEI = "";
}

/**
 * \brief 	Default destructor of class Individual
 *
 * \param 	None
 * \return 	None
 */
Individual::~Individual() {}
