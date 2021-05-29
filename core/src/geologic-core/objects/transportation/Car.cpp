/**
 * \file	Car.cpp
 * \class	Car
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Car object
 *
 * Methods of Car object
 */

#include "geologic-core/objects/transportation/Car.h"
#include "geologic-core/graphe/Edge.h"


/**
 * \brief 	Default constructor of class Car
 *
 * \param 	None
 * \return 	None
 */
Car::Car() {}

/**
 * \brief 	Default destructor of class Car
 *
 * \param 	None
 * \return 	None
 */
Car::~Car() {}

/**
 * \brief 	Behavior of a Car traversing an Edge within a Road graph
 *
 * \param 	edge    The edge to traverse
 * \param   dest    The Id of the destination Node
 * \param   from    The Id of the origin Node
 * \return 	The length of the traversed Edge
 *
 * This will create a deep copy of trajectory
 */
double Car::traverse(Edge *edge, unsigned long long dest, unsigned long long from) {
    return edge->getDistance(this, dest, from);
}
