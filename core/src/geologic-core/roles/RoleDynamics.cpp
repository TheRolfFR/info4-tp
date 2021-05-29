/**
 * \file	RoleDynamics.cpp
 * \class	RoleDynamics
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of RoleDynamics object
 *
 * Methods of RoleDynamics object
 */

#include "geologic-core/roles/RoleDynamics.h"


/**
 * \brief 	Default constructor of class RoleDynamics
 *
 * \param 	None
 * \return 	None
 */
RoleDynamics::RoleDynamics() {}

/**
 * \brief 	Default destructor of class RoleDynamics
 *
 * \param 	None
 * \return 	None
 */
RoleDynamics::~RoleDynamics() {}

/**
 * \brief 	Returns the name of this Role
 *
 * \param 	None
 * \return 	The Role name
 */
std::string RoleDynamics::getRoleName() {
    return ("Dynamics");
}
