/**
 * \file	Edge.cpp
 * \class   Edge
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	05/02/2018
 * \brief	Contains main methods to construct Edge objects
 *
 * \details This class contains several methods used to construct Edge objects
 */

#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"
#include "geologic-core/graphe/Edge.h"
#include "geologic-core/graphe/Node.h"

#include "geologic-core/objects/transportation/Car.h"
#include "geologic-core/objects/transportation/Cycle.h"
#include "geologic-core/objects/transportation/Footman.h"

#include "geologic-core/roles/permissions/Permission.h"
#include "geologic-core/roles/permissions/EmptyPermission.h"
#include "geologic-core/roles/permissions/CarPermission.h"
#include "geologic-core/roles/permissions/CyclePermission.h"
#include "geologic-core/roles/permissions/FootPermission.h"
#include "geologic-core/roles/restrictions/Restriction.h"
#include "geologic-core/roles/restrictions/EmptyRestriction.h"
#include "geologic-core/roles/restrictions/OnewayRestriction.h"
#include "geologic-core/roles/restrictions/NoturnRestriction.h"

#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;
//using namespace GeographicLib;


/**
 * \brief 	Constructor with parameters of class Edge
 *
 * \param 	i   Id of the edge
 * \return 	None
 *
 * Type is set to "unclassified", permissions and restrictions are set to empty
 */
Edge::Edge(unsigned long long id) {
    this->id = id;
    p = new EmptyPermission();
    r = new EmptyRestriction();
    distance = 0.0;
    type = string("unclassified");
}

/**
 * \brief 	Default destructor of class Edge
 *
 * \param 	None
 * \return 	None
 */
Edge::~Edge() {
    delete p;
    delete r;
}

/**
 * \brief 	Adds a node to the edge
 *
 * \param   node    The reference of the Node to add
 * \return 	None
 */
void Edge::addNode(Node* node) {
    if (geometry.getNumPoints() == 0)
        first_node = node->_id;
    else
        last_node = node->_id;
    geometry.addPoint((OGRPoint*) node);
    node->sedge.insert(this->id);
}

/**
 * \brief 	Defines the first Node of this Edge
 *
 * \param 	n   The reference of the first Node
 * \return 	None
 */
void Edge::setFirstNode(unsigned long long nid) {
    first_node = nid;
}

/**
 * \brief 	Defines the last Node of this Edge
 *
 * \param 	n   The reference of the last Node
 * \return 	None
 */
void Edge::setLastNode(unsigned long long nid) {
    last_node = nid;
}

/**
 * \brief 	Defines the first Node of this Edge
 *
 * \param 	n   The reference of the first Node
 * \return 	None
 */
void Edge::setFirstNode(Node *n) {
    first_node = n->_id;
}

/**
 * \brief 	Defines the last Node of this Edge
 *
 * \param 	n   The reference of the last Node
 * \return 	None
 */
void Edge::setLastNode(Node *n) {
    last_node = n->_id;
}

/**
 * \brief 	Manually sets the distance between the two start and final Node
 *
 * \param 	d   The length of the Edge
 * \return 	None
 */
void Edge::setDistance(double d) {
    distance = d;
}

/**
 * \brief 	Computes the distance between the two nodes
 *
 * \param 	None
 * \return 	None
 */
void Edge::setDistance() {
    distance = 0.0;
    if (geometry.getNumPoints() > 1) {
        for (int i = 0; i < geometry.getNumPoints()-1; ++i) {
            OGRPoint p1, p2;
            geometry.getPoint(i, &p1);
            geometry.getPoint(i+1, &p2);
            distance += geoMetrics::distanceTo(&p1, &p2);
        }
    }
    /*/
    if (geometry.getNumPoints() > 1) {
        if (geometry.getSpatialReference() != nullptr && geometry.getSpatialReference()->IsGeographic() != 0) {
            Geodesic geod = Geodesic::WGS84();
            for (int i = 0; i < geometry.getNumPoints()-1; ++i) {
                OGRPoint p1, p2;
                geometry.getPoint(i, &p1);
                geometry.getPoint(i+1, &p2);
                double d = 0.0;
                geod.Inverse(p1.getY(), p1.getX(), p2.getY(), p2.getX(), d);
                distance += d;
            }
        } else {
            for (int i = 0; i < geometry.getNumPoints()-1; ++i) {
                OGRPoint p1, p2;
                geometry.getPoint(i, &p1);
                geometry.getPoint(i+1, &p2);
                distance += p1.Distance(&p2);
            }
        }
    }
    //*/
}

/**
 * \brief 	Manually sets the id of the Edge
 *
 * \param 	i   The Id of the Edge
 * \return 	None
 */
void Edge::setId(unsigned long long i) {
    id = i;
}

/**
 * \brief 	Adds a NoturnRestriction to the Edge
 *
 * \param 	from   The Id of the Restriction
 * \return 	None
 */
void Edge::addEdgeRestriction(unsigned long long from) {
    r = new NoturnRestriction(r, from);
}

/**
 * \brief 	Adds a OnewayRestriction to the Edge
 *
 * \param 	destination_allowed   The Id of the Node in which the OnewayRestriction is available
 * \return 	None
 */
void Edge::addOneway(unsigned long long destination_allowed) {
    r = new OnewayRestriction(r, destination_allowed);
}

/**
 * \brief 	Sets a CarPermission (allows Car on this Edge)
 *
 * \param 	None
 * \return 	None
 */
void Edge::setCarPermission() {
    p = new CarPermission(p);
}

/**
 * \brief 	Sets a CyclePermission (allows Cycle on this Edge)
 *
 * \param 	None
 * \return 	None
 */
void Edge::setCyclePermission() {
    p = new CyclePermission(p);
}

/**
 * \brief 	Sets a FootPermission (allows Pedestrian on this Edge)
 *
 * \param 	None
 * \return 	None
 */
void Edge::setFootPermission() {
    p = new FootPermission(p);
}

/**
 * \brief 	Returns the Id of the Edge
 *
 * \param 	None
 * \return 	id the Id of the Edge
 */
unsigned long long Edge::getId()const {
    return id;
}

/**
 * \brief 	Returns the Id of the first Node of the Edge
 *
 * \param 	None
 * \return 	The Id of the first Node of the Edge
 */
unsigned long long Edge::first()const {
    return first_node;
}

/**
 * \brief 	Returns the Id of the last Node of the Edge
 *
 * \param 	None
 * \return 	The Id of the last Node of the Edge
 */
unsigned long long Edge::last()const  {
    return last_node;
}

/**
 * \brief 	Returns the nodes of this Edge
 *
 * \param 	None
 * \return 	The references of the Nodes of the Edge (OGRLineString)
 */
OGRLineString* Edge::getNodes() {
    return &geometry;
}

/**
 * \brief 	Returns the nodes of this Edge
 *
 * \param 	None
 * \return 	The references of the Nodes of the Edge (OGRLineString)
 */
const OGRLineString* Edge::getNodes()const {
    return &geometry;
}

/**
 * \brief 	Returns the nodes of this Edge
 *
 * \param 	None
 * \return 	The Nodes of the Edge (OGRLineString)
 */
const OGRLineString& Edge::getNodesRef()const {
    return geometry;
}

/**
 * \brief 	Returns the nodes of this Edge
 *
 * \param 	None
 * \return 	The Nodes of the Edge (OGRLineString)
 */
OGRLineString& Edge::getNodesRef() {
    return geometry;
}

/**
 * \brief getDistance returns distance through this edge, for a car coming from edge from and going to node dest
 *
 * \param c a pointer to car instance
 * \param dest the destination node
 * \param from the source edge
 * \return this edge distance if move possible, -1.0 else
 */
double Edge::getDistance(Car* c, unsigned long long dest, unsigned long long from) {
    if (!r->moveForbidden(c, dest, from) && p->moveAllowed(c, dest, from))
        return distance;
    return -1.0;
}

/**
 * \brief getDistance returns distance through this edge, for a pedestrian coming from edge from and going to node dest
 *
 * \param f a pointer to a pedestrian instance
 * \param dest the destination node
 * \param from the source edge
 * \return this edge distance if move possible, -1.0 else
 */
double Edge::getDistance(Footman* c, unsigned long long dest, unsigned long long from) {
    if (p->moveAllowed(c, dest, from))
        return distance;
    return -1.0;
}

/**
 * \brief getDistance returns distance through this edge, for a cycle coming from edge from and going to node dest
 *
 * \param c a pointer to a cycle instance
 * \param dest the destination node
 * \param from the source edge
 * \return this edge distance if move possible, -1.0 else
 */
double Edge::getDistance(Cycle* c, unsigned long long dest, unsigned long long from) {
    if (!r->moveForbidden(c, dest, from) && p->moveAllowed(c, dest, from))
        return distance;
    return -1.0;
}

/**
 * \brief Returns the length of the Edge
 *
 * \param None
 * \return this edge distance
 */
double Edge::getDistance() {
    return distance;
}
