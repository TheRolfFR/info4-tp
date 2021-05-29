/**
 * \file	FootPermission.cpp
 * \class	FootPermission
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of FootPermission object
 *
 * Methods of FootPermission object
 */

#include "geologic-core/roles/permissions/FootPermission.h"
#include "geologic-core/roles/permissions/Permission.h"

#include <iostream>

using namespace std;


/**
 * \brief 	Constructor with parameters of class FootPermission
 *
 * \param 	p   The own address of the Permission
 * \return 	None
 */
FootPermission::FootPermission(Permission* p) {
    this->_p = p;
}

/**
 * \brief 	Default destructor of class Car
 *
 * \param 	None
 * \return 	None
 */
FootPermission::~FootPermission() {
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
bool FootPermission::moveAllowed(Car *m, unsigned long long dest_nid, unsigned long long from_eid) {
    //cout << "FootPermission::moveAllowed(Car *m" << endl;
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
bool FootPermission::moveAllowed(Cycle *m, unsigned long long dest_nid, unsigned long long from_eid) {
    //cout << "FootPermission::moveAllowed(Cycle *m" << endl;
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
bool FootPermission::moveAllowed(Footman *m __attribute__((unused)), unsigned long long dest_nid __attribute__((unused)), unsigned long long from_eid __attribute__((unused))) {
    //cout << "FootPermission::moveAllowed(Footman *m" << endl;
    return true;
}
