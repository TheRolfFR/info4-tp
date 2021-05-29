/**
 * \file	RoleRoadNetworkManager.h
 */

#ifndef RoleRoadNetworkManager_H
#define RoleRoadNetworkManager_H

#include "geologic-core/roles/Role.h"
#include <string>


class RoleRoadNetworkManager : public Role {

    public:
        //*/ -------------------------------------------------
        RoleRoadNetworkManager();
        virtual ~RoleRoadNetworkManager();

        //*/ -------------------------------------------------
        static std::string getRoleName();
};

#endif // RoleRoadNetworkManager_H
