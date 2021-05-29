/**
 * \file	EmptyRestriction.cpp
 * \class	EmptyRestriction
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of EmptyRestriction object
 *
 * Methods of EmptyRestriction object
 */

#include "geologic-core/roles/restrictions/EmptyRestriction.h"


/**
 * \brief 	Surcharging the Permission method
 *
 * \param 	m   The address of a Car (no matter which one)
 * \param   dest_nid    The Id of the destination Node
 * \param   from_eid    The Id of the origin Node
 * \return 	None
 */
bool EmptyRestriction::moveForbidden(Car *m __attribute__((unused)), unsigned long long dest_nid __attribute__((unused)), unsigned long long from_eid __attribute__((unused))) {
    return false;
}

/**
 * \brief 	Surcharging the Permission method
 *
 * \param 	m   The address of a Cycle
 * \param   dest_nid    The Id of the destination Node
 * \param   from_eid    The Id of the origin Node
 * \return 	None
 */
bool EmptyRestriction::moveForbidden(Cycle *m __attribute__((unused)), unsigned long long dest_nid __attribute__((unused)), unsigned long long from_eid __attribute__((unused))) {
    return false;
}

/**
 * \brief 	Surcharging the Permission method
 *
 * \param 	m   The address of a Footman
 * \param   dest_nid    The Id of the destination Node
 * \param   from_eid    The Id of the origin Node
 * \return 	None
 */
bool EmptyRestriction::moveForbidden(Footman *m __attribute__((unused)), unsigned long long dest_nid __attribute__((unused)), unsigned long long from_eid __attribute__((unused))) {
    return false;
}
