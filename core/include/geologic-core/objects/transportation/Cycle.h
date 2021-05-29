/**
 * \file	Cycle.h
 */

#ifndef _CYCLE_
#define _CYCLE_

#include "geologic-core/objects/dynamic/GraphMobileObject.h"
#include "geologic-core/objects/geo/untemporal/GeographicalObject.h"

class GraphMobileObject;
class Edge;
class Node;

class Cycle: public GraphMobileObject, public GeographicalObject {

    public:
        //*/ -------------------------------------------------
        Cycle();
        virtual ~Cycle();

        //*/ -------------------------------------------------
        double traverse(Edge *edge, unsigned long long dest, unsigned long long from);
};

#endif
