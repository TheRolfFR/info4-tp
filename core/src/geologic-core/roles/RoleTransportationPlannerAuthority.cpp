/**
 * \file	RoleTransportationPlannerAuthority.cpp
 * \class	RoleTransportationPlannerAuthority
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of RoleTransportationPlannerAuthority object
 *
 * Methods of RoleTransportationPlannerAuthority object
 */

#include "geologic-core/roles/RoleTransportationPlannerAuthority.h"


/**
 * \brief 	Default constructor of class RoleTransportationPlannerAuthority
 *
 * \param 	None
 * \return 	None
 */
RoleTransportationPlannerAuthority::RoleTransportationPlannerAuthority() {}

/**
 * \brief 	Default destructor of class RoleTransportationPlannerAuthority
 *
 * \param 	None
 * \return 	None
 */
RoleTransportationPlannerAuthority::~RoleTransportationPlannerAuthority() {}

/**
 * \brief 	Returns the name of this Role
 *
 * \param 	None
 * \return 	The Role name
 */
std::string RoleTransportationPlannerAuthority::getRoleName() {
    return ("TransportationPlannerAuthority");
}
