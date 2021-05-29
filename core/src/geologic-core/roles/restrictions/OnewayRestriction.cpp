/**
 * \file	OnewayRestriction.cpp
 * \class	OnewayRestriction
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of OnewayRestriction object
 *
 * Methods of OnewayRestriction object
 */

#include "geologic-core/roles/restrictions/OnewayRestriction.h"


/**
 * \brief 	Constructor with parameters of class OnewayRestriction
 *
 * \param 	p   The own address of the Permission
 * \return 	None
 */
OnewayRestriction::OnewayRestriction(Restriction *r, unsigned long long dest_nid) {
    this->destination_allowed_nid = dest_nid;
    this->_r = r;
}

/**
 * \brief 	Default destructor of class Car
 *
 * \param 	None
 * \return 	None
 */
OnewayRestriction::~OnewayRestriction() {
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
bool OnewayRestriction::moveForbidden(Car *m, unsigned long long dest_nid, unsigned long long from_eid) {
  if (dest_nid != destination_allowed_nid) return true;
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
bool OnewayRestriction::moveForbidden(Cycle *m, unsigned long long dest_nid, unsigned long long from_eid) {
  if (dest_nid != destination_allowed_nid) return true;
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
bool OnewayRestriction::moveForbidden(Footman *m, unsigned long long dest_nid, unsigned long long from_eid) {
  return _r->moveForbidden(m, dest_nid, from_eid);
}
