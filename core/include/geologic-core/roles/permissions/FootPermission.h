/**
 * \file	FootPermission.h
 */

#ifndef _FOOTPERMISSION_
#define _FOOTPERMISSION_

#include "Permission.h"

class Car;
class Cycle;
class Footman;
class Node;
class Edge;

class FootPermission: public Permission {

    public:
        //*/ -------------------------------------------------
        FootPermission(Permission* p);

        virtual ~FootPermission();
        virtual bool moveAllowed(Car* m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveAllowed(Cycle* m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveAllowed(Footman* m, unsigned long long dest_nid, unsigned long long from_eid);

    protected:
        //*/ -------------------------------------------------
        Permission* _p;
};

#endif /* _FOOTPERMISSION_ */
