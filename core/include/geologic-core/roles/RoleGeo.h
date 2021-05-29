/**
 * \file	RoleGeo.h
 */

#ifndef RoleGeo_H
#define RoleGeo_H

#include "geologic-core/roles/Role.h"
//#include "geologic-core/objects/geo/untemporal/Bbox.h"
#include <string>


class RoleGeo : public Role {

    public:
        //*/ -------------------------------------------------
        RoleGeo();
        virtual ~RoleGeo();

        //*/ -------------------------------------------------
        static std::string getRoleName();
        //virtual Bbox* getGlobalBbox() = 0;
};

#endif // RoleGeo_H
