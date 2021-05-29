/**
 * \file	EmptyPermission.h
 */

#ifndef _EMPTYPERMISSION_
#define _EMPTYPERMISSION_

#include "Permission.h"

class Car;
class Cycle;
class Footman;

class EmptyPermission: public Permission {

    public:
        //*/ -------------------------------------------------
        virtual bool moveAllowed(Car* m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveAllowed(Cycle* m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveAllowed(Footman* m, unsigned long long dest_nid, unsigned long long from_eid);
};

#endif /* _EMPTYPERMISSION_ */
