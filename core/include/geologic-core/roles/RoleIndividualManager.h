/**
 * \file	RoleIndividualManager.h
 */

#ifndef RoleIndividualManager_H
#define RoleIndividualManager_H

#include "geologic-core/roles/Role.h"
#include <string>


class RoleIndividualManager : public Role {

    public:
        //*/ -------------------------------------------------
        RoleIndividualManager();
        virtual ~RoleIndividualManager();

        //*/ -------------------------------------------------
        static std::string getRoleName();
};

#endif // RoleIndividualManager_H
