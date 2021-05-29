/**
 * \file	Role.cpp
 * \class	Role
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Role object
 *
 * A role is a set of behaviors that any object can subscribe to. In means that this object can, and has to return information when asked.
 * The information asked are specific to a given role. A class can subscribe different roles.
 */

#include "geologic-core/roles/Role.h"


/**
 * \brief 	Default constructor of class Role
 *
 * \param 	None
 * \return 	None
 */
Role::Role() {}

/**
 * \brief 	Default destructor of class Role
 *
 * \param 	None
 * \return 	None
 */
Role::~Role() {}
