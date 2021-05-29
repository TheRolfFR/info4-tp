/**
 * \file	RoleDynamics.h
 */

#ifndef RoleDynamics_H
#define RoleDynamics_H

#include "geologic-core/roles/Role.h"
//#include "geologic-core/objects/dynamic/aggregated/GeoZoneTemporalODMatrix.h"
//#include "geologic-core/objects/dynamic/aggregated/MeshTemporalODMatrix.h"
//#include "geologic-core/objects/geo/untemporal/MeshGrid.h"
#include <string>


class RoleDynamics : public Role {

    public:
        //*/ -------------------------------------------------
        RoleDynamics();
        virtual ~RoleDynamics();

        //*/ -------------------------------------------------
        static std::string getRoleName();
//        virtual GeoZoneTemporalODMatrix* getGeoZoneTemporalODMatrix(std::unordered_map<std::string, std::string>* parameters,
//                                                                    std::unordered_map<std::string, GeoZone*>* zones) = 0;
//        virtual MeshTemporalODMatrix* getMeshTemporalODMatrix(std::unordered_map<std::string, std::string>* parameters, MeshGrid* grid) = 0;
};

#endif // RoleDynamics_H
