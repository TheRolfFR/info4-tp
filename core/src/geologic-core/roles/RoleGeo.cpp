/**
 * \file	RoleGeo.cpp
 * \class	RoleGeo
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of RoleGeo object
 *
 * Methods of RoleGeo object
 */

#include "geologic-core/roles/RoleGeo.h"


/**
 * \brief 	Default constructor of class RoleGeo
 *
 * \param 	None
 * \return 	None
 */
RoleGeo::RoleGeo() {}

/**
 * \brief 	Default destructor of class RoleGeo
 *
 * \param 	None
 * \return 	None
 */
RoleGeo::~RoleGeo() {}

/**
 * \brief 	Returns the name of this Role
 *
 * \param 	None
 * \return 	The Role name
 */
std::string RoleGeo::getRoleName() {
    return ("Geo");
}
