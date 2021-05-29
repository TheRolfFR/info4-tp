/**
 * \file	Permission.h
 */

#ifndef _PERMISSION_
#define _PERMISSION_

class Car;
class Cycle;
class Footman;
class Node;
class Edge;

class Permission {

    public:
        //*/ -------------------------------------------------
        virtual ~Permission() {}

        //*/ -------------------------------------------------
        virtual bool moveAllowed(Car* m, unsigned long long dest_nid, unsigned long long from_eid) = 0;
        virtual bool moveAllowed(Cycle* m, unsigned long long dest_nid, unsigned long long from_eid) = 0;
        virtual bool moveAllowed(Footman* m, unsigned long long dest_nid, unsigned long long from_eid) = 0;
};

#endif /* _PERMISSION_ */
