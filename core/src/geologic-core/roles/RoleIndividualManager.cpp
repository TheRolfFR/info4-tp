/**
 * \file	RoleIndividualManager.cpp
 * \class	RoleIndividualManager
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of RoleIndividualManager object
 *
 * Methods of RoleIndividualManager object
 */

#include "geologic-core/roles/RoleIndividualManager.h"


/**
 * \brief 	Default constructor of class RoleIndividualManager
 *
 * \param 	None
 * \return 	None
 */
RoleIndividualManager::RoleIndividualManager() {}

/**
 * \brief 	Default destructor of class RoleIndividualManager
 *
 * \param 	None
 * \return 	None
 */
RoleIndividualManager::~RoleIndividualManager() {}

/**
 * \brief 	Returns the name of this Role
 *
 * \param 	None
 * \return 	The Role name
 */
std::string RoleIndividualManager::getRoleName() {
    return ("IndividualManager");
}
