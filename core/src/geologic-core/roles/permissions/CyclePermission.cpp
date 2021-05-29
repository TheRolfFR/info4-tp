/**
 * \file	CyclePermission.cpp
 * \class	CyclePermission
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of CyclePermission object
 *
 * Methods of CyclePermission object
 */

#include "geologic-core/roles/permissions/CyclePermission.h"
#include "geologic-core/roles/permissions/Permission.h"

#include <iostream>

using namespace std;


/**
 * \brief 	Constructor with parameters of class CyclePermission
 *
 * \param 	p   The own address of the Permission
 * \return 	None
 */
CyclePermission::CyclePermission(Permission* p) {
    this->_p = p;
}

/**
 * \brief 	Default destructor of class Car
 *
 * \param 	None
 * \return 	None
 */
CyclePermission::~CyclePermission() {
    delete _p;
}

/**
 * \brief 	Surcharging the Permission method
 *
 * \param 	m   The address of a Car (no matter which one)
 * \param   dest_nid    The Id of the destination Node
 * \param   from_eid    The Id of the origin Node
 * \return 	None
 */
bool CyclePermission::moveAllowed(Car *m, unsigned long long dest_nid, unsigned long long from_eid) {
    //cout << "CyclePermission::moveAllowed(Car *m" << endl;
    return _p->moveAllowed(m, dest_nid, from_eid);
}

/**
 * \brief 	Surcharging the Permission method
 *
 * \param 	m   The address of a Cycle
 * \param   dest_nid    The Id of the destination Node
 * \param   from_eid    The Id of the origin Node
 * \return 	None
 */
bool CyclePermission::moveAllowed(Cycle *m __attribute__((unused)), unsigned long long dest_nid __attribute__((unused)), unsigned long long from_eid __attribute__((unused))) {
    //cout << "CyclePermission::moveAllowed(Cycle *m" << endl;
    return true;
}

/**
 * \brief 	Surcharging the Permission method
 *
 * \param 	m   The address of a Footman
 * \param   dest_nid    The Id of the destination Node
 * \param   from_eid    The Id of the origin Node
 * \return 	None
 */
bool CyclePermission::moveAllowed(Footman *m, unsigned long long dest_nid, unsigned long long from_eid) {
    //cout << "CyclePermission::moveAllowed(Footman *m" << endl;
    return _p->moveAllowed(m, dest_nid, from_eid);
}
