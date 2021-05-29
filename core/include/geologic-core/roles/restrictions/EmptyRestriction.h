/**
 * \file	EmptyRestriction.h
 */

#ifndef _EMPTYRESTRICTION_
#define _EMPTYRESTRICTION_

#include "Restriction.h"

class Car;
class Cycle;
class Footman;
class Node;
class Edge;

class EmptyRestriction: public Restriction {

    public:
        //*/ -------------------------------------------------
        virtual bool moveForbidden(Car *m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveForbidden(Cycle *m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveForbidden(Footman *m, unsigned long long dest_nid, unsigned long long from_eid);
};

#endif /* _EMPTYRESTRICTION_ */
