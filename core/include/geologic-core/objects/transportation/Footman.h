/**
 * \file	Footman.h
 */

#ifndef _FOOTMAN_
#define _FOOTMAN_

#include "geologic-core/objects/dynamic/GraphMobileObject.h"
#include "geologic-core/objects/geo/untemporal/GeographicalObject.h"

class GraphMobileObject;
class Edge;
class Node;

class Footman: public GraphMobileObject, public GeographicalObject {

    public:
        //*/ -------------------------------------------------
        Footman();
        virtual ~Footman();

        //*/ -------------------------------------------------
        double traverse(Edge *edge, unsigned long long dest, unsigned long long from);
};

#endif
