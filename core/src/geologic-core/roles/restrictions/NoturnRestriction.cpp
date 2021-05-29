/**
 * \file	NoturnRestriction.cpp
 * \class	NoturnRestriction
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of NoturnRestriction object
 *
 * Methods of NoturnRestriction object
 */

#include "geologic-core/roles/restrictions/NoturnRestriction.h"


/**
 * \brief 	Constructor with parameters of class NoturnRestriction
 *
 * \param 	p   The own address of the Permission
 * \return 	None
 */
NoturnRestriction::NoturnRestriction(Restriction *r, unsigned long long eid) {
    this->previous_forbidden_eid = eid;
    this->_r = r;
}

/**
 * \brief 	Default destructor of class Car
 *
 * \param 	None
 * \return 	None
 */
NoturnRestriction::~NoturnRestriction() {
    delete _r;
}

/**
 * \brief 	Surcharging the Restriction method
 *
 * \param 	m   The address of a Car
 * \param   dest_nid    The Id of the destination Node
 * \param   from_eid    The Id of the origin Node
 * \return 	None
 */
bool NoturnRestriction::moveForbidden(Car *m, unsigned long long dest_nid, unsigned long long from_eid) {
  if (from_eid != previous_forbidden_eid) return true;
  return _r->moveForbidden(m, dest_nid, from_eid);
}

/**
 * \brief 	Surcharging the Restriction method
 *
 * \param 	m   The address of a Cycle
 * \param   dest_nid    The Id of the destination Node
 * \param   from_eid    The Id of the origin Node
 * \return 	None
 */
bool NoturnRestriction::moveForbidden(Cycle *m, unsigned long long dest_nid, unsigned long long from_eid) {
  if (from_eid != previous_forbidden_eid) return true;
  return _r->moveForbidden(m, dest_nid, from_eid);
}

/**
 * \brief 	Surcharging the Restriction method
 *
 * \param 	m   The address of a Footman
 * \param   dest_nid    The Id of the destination Node
 * \param   from_eid    The Id of the origin Node
 * \return 	None
 */
bool NoturnRestriction::moveForbidden(Footman *m, unsigned long long dest_nid, unsigned long long from_eid) {
  return _r->moveForbidden(m, dest_nid, from_eid);
}
