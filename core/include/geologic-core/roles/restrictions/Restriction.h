/**
 * \file	Restriction.h
 */

#ifndef _RESTRICTION_
#define _RESTRICTION_

class Car;
class Cycle;
class Footman;
class Node;
class Edge;

class Restriction {

        public:
            //*/ -------------------------------------------------
            virtual ~Restriction() {}

            //*/ -------------------------------------------------
            virtual bool moveForbidden(Car *m, unsigned long long dest_nid, unsigned long long from_eid) = 0;
            virtual bool moveForbidden(Cycle *m, unsigned long long dest_nid, unsigned long long from_eid) = 0;
            virtual bool moveForbidden(Footman *m, unsigned long long dest_nid, unsigned long long from_eid) = 0;
};

#endif /* _RESTRICTION_ */
