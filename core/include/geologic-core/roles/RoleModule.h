/**
 * \file	RoleModule.h
 */

#ifndef RoleModule_H
#define RoleModule_H

//#include "geologic-core/core/geologic-core_global.h"
#include "geologic-core/roles/Role.h"
#include <string>
#include <vector>

//GEOLOGICCORESHARED_EXPORT
class  RoleModule : public Role {

    public:
        //*/ -------------------------------------------------
        RoleModule();
        virtual ~RoleModule();

        //*/ -------------------------------------------------
        static std::string getRoleName();
        virtual std::vector<std::string> getSubscribedRoles() = 0;
};

#endif // RoleModule_H
