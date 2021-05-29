/**
 * \file	CarPermission.h
 */

#ifndef _CARPERMISSION_
#define _CARPERMISSION_

#include "geologic-core/roles/permissions/Permission.h"

class Car;
class Cycle;
class Footman;

class CarPermission: public Permission {

    public:
        //*/ -------------------------------------------------
        CarPermission(Permission* p);

        virtual ~CarPermission();
        virtual bool moveAllowed(Car* m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveAllowed(Cycle* m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveAllowed(Footman* m, unsigned long long dest_nid, unsigned long long from_eid);

    protected:
        //*/ -------------------------------------------------
        Permission* _p;
};

#endif /* _CARPERMISSION_ */
