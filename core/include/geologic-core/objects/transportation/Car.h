/**
 * \file	Car.h
 */

#ifndef _CAR_
#define _CAR_

#include "geologic-core/objects/dynamic/GraphMobileObject.h"
#include "geologic-core/objects/geo/untemporal/GeographicalObject.h"

class GraphMobileObject;
class Edge;
class Node;

class Car: public GraphMobileObject, public GeographicalObject {

    public:
        //*/ -------------------------------------------------
        Car();
        virtual ~Car();

        //*/ -------------------------------------------------
        double traverse(Edge *edge, unsigned long long dest, unsigned long long from);
};

#endif
