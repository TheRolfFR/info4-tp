/**
 * \file	RoleTransportationPlannerAuthority.h
 */

#ifndef RoleTransportationPlannerAuthority_H
#define RoleTransportationPlannerAuthority_H

#include "geologic-core/roles/Role.h"
#include <string>


class RoleTransportationPlannerAuthority : public Role {

    public:
        //*/ -------------------------------------------------
        RoleTransportationPlannerAuthority();
        virtual ~RoleTransportationPlannerAuthority();

        //*/ -------------------------------------------------
        static std::string getRoleName();
};

#endif // RoleTransportationPlannerAuthority_H
