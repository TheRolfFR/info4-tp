/**
 * \file	RoleRoadNetworkManager.cpp
 * \class	RoleRoadNetworkManager
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of RoleRoadNetworkManager object
 *
 * Methods of RoleRoadNetworkManager object
 */

#include "geologic-core/roles/RoleRoadNetworkManager.h"


/**
 * \brief 	Default constructor of class RoleRoadNetworkManager
 *
 * \param 	None
 * \return 	None
 */
RoleRoadNetworkManager::RoleRoadNetworkManager() {}

/**
 * \brief 	Default destructor of class RoleRoadNetworkManager
 *
 * \param 	None
 * \return 	None
 */
RoleRoadNetworkManager::~RoleRoadNetworkManager() {}

/**
 * \brief 	Returns the name of this Role
 *
 * \param 	None
 * \return 	The Role name
 */
std::string RoleRoadNetworkManager::getRoleName() {
    return ("RoadNetworkManager");
}
