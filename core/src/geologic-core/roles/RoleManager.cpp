/**
 * \file	RoleManager.cpp
 * \class	RoleManager
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of RoleManager object
 *
 * This class allows any object to manage the different roles that are held by the different classes of the project.
 * The object hold the references of all the "actors", and their "roles"
 */

#include "geologic-core/roles/RoleManager.h"


/**
 * \brief 	Default constructor of class RoleManager
 *
 * \param 	None
 * \return 	None
 */
RoleManager::RoleManager() {}

/**
 * \brief 	Default destructor of class RoleManager
 *
 * \param 	None
 * \return 	None
 */
RoleManager::~RoleManager() {}

/**
 * \brief 	Returns the name of this Role
 *
 * \param 	None
 * \return 	The Role name
 */
std::string RoleManager::getRoleName() {
    return ("Manager");
}
