/**
 * \file	RoleModule.cpp
 * \class	RoleModule
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of RoleModule object
 *
 * This role allows any class to register as the main class of a project (module)
 * This project can be then referred as a Module.
 * The Module object can subscribe also to different other roles (maps, transportation, individual managers, etc.)
 * The Module has to returns the different roles a project has subscribed to.
 */

#include "geologic-core/roles/RoleModule.h"


/**
 * \brief 	Default constructor of class RoleModule
 *
 * \param 	None
 * \return 	None
 */
RoleModule::RoleModule() {}

/**
 * \brief 	Default destructor of class RoleModule
 *
 * \param 	None
 * \return 	None
 */
RoleModule::~RoleModule() {}

/**
 * \brief 	Returns the name of this Role
 *
 * \param 	None
 * \return 	The Role name
 */
std::string RoleModule::getRoleName() {
    return ("Module");
}
