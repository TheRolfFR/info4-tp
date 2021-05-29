/**
 * \file	Cycle.cpp
 * \class	Cycle
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Cycle object
 *
 * Methods of Cycle object
 */

#include "geologic-core/objects/transportation/Cycle.h"
#include "geologic-core/graphe/Edge.h"


/**
 * \brief 	Default constructor of class Cycle
 *
 * \param 	None
 * \return 	None
 */
Cycle::Cycle() {}

/**
 * \brief 	Default destructor of class Cycle
 *
 * \param 	None
 * \return 	None
 */
Cycle::~Cycle() {}

/**
 * \brief 	Behavior of a Cycle traversing an Edge within a Road graph
 *
 * \param 	edge    The edge to traverse
 * \param   dest    The Id of the destination Node
 * \param   from    The Id of the origin Node
 * \return 	The length of the traversed Edge
 *
 * This will create a deep copy of trajectory
 */
double Cycle::traverse(Edge *edge, unsigned long long dest, unsigned long long from) {
    return edge->getDistance(this, dest, from);
}
