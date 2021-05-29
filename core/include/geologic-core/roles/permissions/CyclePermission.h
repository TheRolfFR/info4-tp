/**
 * \file	CyclePermission.h
 */

#ifndef _CYCLEPERMISSION_
#define _CYCLEPERMISSION_

#include "Permission.h"

class Car;
class Cycle;
class Footman;

class CyclePermission: public Permission {

    public:
        //*/ -------------------------------------------------
        CyclePermission(Permission* p);

        virtual ~CyclePermission();
        virtual bool moveAllowed(Car* m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveAllowed(Cycle* m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveAllowed(Footman* m, unsigned long long dest_nid, unsigned long long from_eid);

    protected:
        //*/ -------------------------------------------------
        Permission* _p;
};

#endif /* _CYCLEPERMISSION_ */
