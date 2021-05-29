#ifndef _ONEWAYRESTRICTION_
#define _ONEWAYRESTRICTION_

#include "geologic-core/roles/restrictions/Restriction.h"
#include "geologic-core/graphe/Edge.h"

class Car;
class Cycle;
class Footman;
class Node;
class Edge;

class OnewayRestriction: public Restriction {

    public:
        //*/ -------------------------------------------------
        OnewayRestriction(Restriction *r, unsigned long long dest_nid);

        virtual ~OnewayRestriction();
        virtual bool moveForbidden(Car *m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveForbidden(Cycle *m, unsigned long long dest_nid, unsigned long long from_eid);
        virtual bool moveForbidden(Footman *m, unsigned long long dest_nid, unsigned long long from_eid);

    protected:
        //*/ -------------------------------------------------
        unsigned long long destination_allowed_nid;
        Restriction *_r;
};

#endif /* _ONEWAYRESTRICTION_ */
