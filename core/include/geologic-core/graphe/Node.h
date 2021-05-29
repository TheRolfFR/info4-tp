/**
 * \file	Node.h
 */

#ifndef NODE_H
#define NODE_H

#include <ogr_geometry.h>
#include <set>

class Edge;

class Node: public OGRPoint {

    public:
        //*/ -------------------------------------------------
        Node() = delete; // Default constructor is forbidden (id has to be defined)
        Node(long long id, double x=0.0, double y=0.0, double z=0.0);
        Node(const Node &n);

        Node &operator=(const Node &n);
        bool operator==(const Node &n);

        double straightDistance(Node* node);

        //*/ -------------------------------------------------
        unsigned long long _id;
        std::set<unsigned long long> sedge;
};

#endif // NODE_H
