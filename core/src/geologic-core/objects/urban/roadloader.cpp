/**
 * \file	Mobile.cpp
 * \class	Mobile
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Mobile object
 *
 * Methods of Mobile object
 */

#include "geologic-core/objects/urban/roadloader.h"
#include "geologic-core/graphe/Node.h"
#include "geologic-core/graphe/Edge.h"

RoadLoader::RoadLoader(OGRSpatialReference *ref): dataref(ref) {}

std::map<unsigned long long, std::unique_ptr<Node> > RoadLoader::getNodes() {
    return std::move(mNode);
}

std::map<unsigned long long, std::unique_ptr<Edge> > RoadLoader::getEdges() {
    return std::move(mEdge);
}
