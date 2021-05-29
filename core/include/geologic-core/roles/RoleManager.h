/**
 * \file	RoleManager.h
 */

#ifndef RoleManager_H
#define RoleManager_H

#include "geologic-core/roles/Role.h"
#include "geologic-core/roles/RoleModule.h"
#include "geologic-core/roles/RoleDynamics.h"
#include "geologic-core/roles/RoleGeo.h"
#include "geologic-core/roles/RoleIndividualManager.h"
#include "geologic-core/roles/RoleRoadNetworkManager.h"
#include "geologic-core/roles/RoleTransportationPlannerAuthority.h"
#include "geologic-core/superClasses/Module.h"
#include <string>
#include <unordered_map>


class RoleManager : public Role {

    public:
        //*/ -------------------------------------------------
        RoleManager();
        virtual ~RoleManager();

        //*/ -------------------------------------------------
        static std::string getRoleName();
        virtual void getModules(std::string roles="") = 0;

    protected:
        //*/ -------------------------------------------------
        std::unordered_map<std::string, Module*> modules;
        std::unordered_map<std::string, RoleModule*> rolesMod;
        std::unordered_map<std::string, RoleDynamics*> rolesDyn;
        std::unordered_map<std::string, RoleGeo*> rolesGeo;
        std::unordered_map<std::string, RoleIndividualManager*> rolesIndMan;
        std::unordered_map<std::string, RoleRoadNetworkManager*> rolesRoaNetMan;
        std::unordered_map<std::string, RoleTransportationPlannerAuthority*> rolesTraPlaAut;
};

#endif // RoleManager_H
