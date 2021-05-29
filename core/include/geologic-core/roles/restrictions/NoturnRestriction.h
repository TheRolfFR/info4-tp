/**
 * \file	NoturnRestriction.h
 */

#ifndef _NOTURNRESTRICTION_
#define _NOTURNRESTRICTION_

#include "geologic-core/roles/restrictions/Restriction.h"

class Car;
class Cycle;
class Footman;

class NoturnRestriction: public Restriction {

    public:
        //*/ -------------------------------------------------
        NoturnRestriction(Restriction *r, unsigned long long eid);

        virtual ~NoturnRestriction();
        virtual bool moveForbidden(Car *m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveForbidden(Cycle *m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveForbidden(Footman *m, unsigned long long dest_nid, unsigned long long from_eid);

    protected:
        //*/ -------------------------------------------------
        unsigned long long previous_forbidden_eid;
        Restriction *_r;
};

#endif /* _NOTURNRESTRICTION_ */
