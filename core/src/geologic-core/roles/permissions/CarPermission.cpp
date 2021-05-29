/**
 * \file	CarPermission.cpp
 * \class	CarPermission
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of CarPermission object
 *
 * Methods of CarPermission object
 */

#include "geologic-core/roles/permissions/CarPermission.h"
#include "geologic-core/roles/permissions/Permission.h"

#include <iostream>

using namespace std;


/**
 * \brief 	Constructor with parameters of class CarPermission
 *
 * \param 	p   The own address of the Permission
 * \return 	None
 */
CarPermission::CarPermission(Permission* p) {
    this->_p = p;
}

/**
 * \brief 	Default destructor of class Car
 *
 * \param 	None
 * \return 	None
 */
CarPermission::~CarPermission() {
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
bool CarPermission::moveAllowed(Car *m __attribute__((unused)), unsigned long long dest_nid __attribute__((unused)), unsigned long long from_eid __attribute__((unused))) {
    //cout << "CarPermission::moveAllowed(Car *m" << endl;
    return true;
}

/**
 * \brief 	Surcharging the Permission method
 *
 * \param 	m   The address of a Cycle
 * \param   dest_nid    The Id of the destination Node
 * \param   from_eid    The Id of the origin Node
 * \return 	None
 */
bool CarPermission::moveAllowed(Cycle *m, unsigned long long dest_nid, unsigned long long from_eid) {
    //cout << "CarPermission::moveAllowed(Cycle *m" << endl;
    return _p->moveAllowed(m, dest_nid, from_eid);
}

/**
 * \brief 	Surcharging the Permission method
 *
 * \param 	m   The address of a Footman
 * \param   dest_nid    The Id of the destination Node
 * \param   from_eid    The Id of the origin Node
 * \return 	None
 */
bool CarPermission::moveAllowed(Footman *m, unsigned long long dest_nid, unsigned long long from_eid) {
    //cout << "CarPermission::moveAllowed(Footman *m" << endl;
    return _p->moveAllowed(m, dest_nid, from_eid);
}
