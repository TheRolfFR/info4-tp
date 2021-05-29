/**
 * \file	GraphMobileObject.h
 */

#ifndef _MOBILE_
#define _MOBILE_

#include "geologic-core/objects/dynamic/MobileObject.h"
#include <cstdlib>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <string>

class Edge;
class Node;

class GraphMobileObject : public MobileObject {

    public:
        //*/ -------------------------------------------------
        GraphMobileObject();
        virtual ~GraphMobileObject();

        //*/ -------------------------------------------------
        virtual double traverse(Edge*, unsigned long long dest, unsigned long long from) = 0;

        std::vector<Node*> &getPathnode();
        std::vector<Edge*> &getPathedge();

        virtual Node* getStartnode();
        virtual Node* getArrivalnode();

        virtual void setStartnode(Node* node);
        virtual void setArrivalnode(Node* node);

    protected:
        //*/ -------------------------------------------------
        std::vector<Node*> path_nodes;
        std::vector<Edge*> path_edges;

        Node* start_node;
        Node* arrival_node;
};

#endif
