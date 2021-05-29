/**
 * \file	Edge.h
 */

#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <string>
#include <ogr_geometry.h>

class Car;
class Cycle;
class Footman;
class Node;
class Permission;
class Restriction;

class Edge {

    public:
        //*/ -------------------------------------------------
        Edge() = delete; // Must have an id
        Edge(unsigned long long i);
        virtual ~Edge();

        //*/ -------------------------------------------------
        void addNode(Node* node);

        void setFirstNode(unsigned long long nid);
        void setLastNode(unsigned long long nid);
        void setFirstNode(Node* n);
        void setLastNode(Node* n);

        void setDistance(double d);
        void setDistance();
        void setId(unsigned long long i);

        void addEdgeRestriction(unsigned long long from);
        void addOneway(unsigned long long destination_allowed);

        void setCarPermission();
        void setCyclePermission();
        void setFootPermission();

        unsigned long long getId()const;
        unsigned long long first()const;
        unsigned long long last()const;

        OGRLineString* getNodes();
        const OGRLineString* getNodes()const;
        const OGRLineString& getNodesRef()const;
        OGRLineString& getNodesRef();

        virtual double getDistance(Car *c, unsigned long long dest, unsigned long long from);
        virtual double getDistance(Footman *f, unsigned long long dest, unsigned long long from);
        virtual double getDistance(Cycle *c, unsigned long long dest, unsigned long long from);
        double getDistance();

        //*/ -------------------------------------------------
        unsigned long long id;
        std::string type;

    private:
        //*/ -------------------------------------------------
        OGRLineString geometry;
        unsigned long long first_node; //< Reference to first node by id
        unsigned long long last_node; //< Reference to first node by id
        double distance; //< Geographical distance from first node to last node of geometry.
        Permission* p; //< Permissions for various kinds of mobile (pedestrian, car, etc.)
        Restriction* r; //< Restrictions applied to the edge (oneway street and no turn).
};

#endif // EDGE_H
