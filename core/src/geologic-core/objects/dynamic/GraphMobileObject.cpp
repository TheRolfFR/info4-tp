/**
 * \file	GraphMobileObject.cpp
 * \class	GraphMobileObject
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of GraphMobileObject object
 *
 * A GraphMobileObject object is representing a succession of Node and Edge in a graph. It represents a Trajectory within a graph
 */

#include "geologic-core/objects/dynamic/GraphMobileObject.h"
#include "geologic-core/graphe/Edge.h"
#include "geologic-core/graphe/Node.h"
#include <cstdlib>
#include <map>
#include <cfloat>
#include <iostream>

using namespace std;


/**
 * \brief 	Default constructor of class GraphMobileObject
 *
 * \param 	None
 * \return 	None
 *
 * Start Node and end Node are set to nullptr
 */
GraphMobileObject::GraphMobileObject() {
    start_node = nullptr;
    arrival_node = nullptr;
}

/**
 * \brief 	Default destructor of class GraphMobileObject
 *
 * \param 	None
 * \return 	None
 */
GraphMobileObject::~GraphMobileObject() {}

/**
 * \brief 	Returns the different Node followed by the MobileObject
 *
 * \param 	None
 * \return 	The path of Node
 */
std::vector<Node*>& GraphMobileObject::getPathnode() {
    return path_nodes;
}

/**
 * \brief 	Returns the different Edge followed by the MobileObject
 *
 * \param 	None
 * \return 	The path of Edge
 */
std::vector<Edge*>& GraphMobileObject::getPathedge() {
    return path_edges;
}

/**
 * \brief 	Returns the first Node of the path
 *
 * \param 	None
 * \return 	The first Node of the path
 */
Node* GraphMobileObject::getStartnode() {
    return start_node;
}

/**
 * \brief 	Returns the last Node of the path
 *
 * \param 	None
 * \return 	The last Node of the path
 */
Node* GraphMobileObject::getArrivalnode() {
    return arrival_node;
}

/**
 * \brief 	Sets the first Node of the path
 *
 * \param 	node the first Node
 * \return 	None
 */
void GraphMobileObject::setStartnode(Node* node) {
    path_nodes.push_back(node);
    start_node = node;
}

/**
 * \brief 	Sets the last Node of the path
 *
 * \param 	node the last Node
 * \return 	None
 */
void GraphMobileObject::setArrivalnode(Node* node) {
    arrival_node = node;
}

