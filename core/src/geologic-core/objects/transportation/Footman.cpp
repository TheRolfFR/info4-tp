/**
 * \file	Footman.cpp
 * \class	Footman
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Footman object
 *
 * Methods of Footman object
 */

#include "geologic-core/objects/transportation/Footman.h"
#include "geologic-core/graphe/Edge.h"


/**
 * \brief 	Default constructor of class Footman
 *
 * \param 	None
 * \return 	None
 */
Footman::Footman() {}

/**
 * \brief 	Default destructor of class Footman
 *
 * \param 	None
 * \return 	None
 */
Footman::~Footman() {}

/**
 * \brief 	Behavior of a Footman traversing an Edge within a Road graph
 *
 * \param 	edge    The edge to traverse
 * \param   dest    The Id of the destination Node
 * \param   from    The Id of the origin Node
 * \return 	The length of the traversed Edge
 *
 * This will create a deep copy of trajectory
 */
double Footman::traverse(Edge *edge, unsigned long long dest, unsigned long long from) {
    return edge->getDistance(this, dest, from);
}
