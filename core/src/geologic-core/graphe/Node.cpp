/**
 * \file	Node.cpp
 * \class	Node
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Node object
 *
 * Methods of Node object, basic element of a graph. Based on OSM nodes.
 */

#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"
#include "geologic-core/graphe/Node.h"
#include "geologic-core/graphe/Edge.h"
#include <utility>
#include <cstring>

using namespace std;
//using namespace GeographicLib;


/**
 * \brief 	Constructor with parameters of class Node
 *
 * \param 	id  The Id of the Node
 * \param 	x   The x position
 * \param 	y   The y position
 * \param 	z   The z position
 * \return 	None
 *
 * Creates an OGRPoint with the (x,y,z) triplet
 */
Node::Node(long long id, double x, double y, double z): OGRPoint(x, y, z) {
    this->_id = id;
}

/**
 * \brief 	Copy constructor of class Node
 *
 * \param 	n   The Node to copy
 * \return 	None
 */
Node::Node(const Node &n): OGRPoint(n) {
    this->_id = n._id;
}

/**
 * \brief 	Surcharging of operator = for Node
 *
 * \param 	n   the reference of the Node to copy
 * \return 	The reference of the copied Node
 */
Node &Node::operator=(const Node &n) {
    OGRPoint::operator = (n);
    _id = n._id;
    sedge = n.sedge;
    return *this;
}

/**
 * \brief 	Surcharging of operator == for Node
 *
 * \param 	n   the reference of the Node to compare
 * \return 	True if the two Node id are equals, False otherwise
 */
bool Node::operator==(const Node &n) {
    return _id == n._id;
}

/**
 * \brief 	Computes the distance (crow flight) with another Node
 *
 * \param 	node   the reference of the distant Node
 * \return 	The distance with the distant Node (in m)
 */
double Node::straightDistance(Node *node) {
    /*/
    double distance = -1.0;
    char* unit;
    node->getSpatialReference()->GetLinearUnits(&unit);
    if (strncmp(unit, "metre", 5) == 0) {
        distance = node->Distance(this);
    } else {
        const Geodesic& geod = Geodesic::WGS84();
        geod.Inverse(getY(), getX(), node->getY(), node->getX(), distance);
    }
    return distance;
    //*/
    return geoMetrics::distanceTo(this, node);
}
