/**
 * \file	MobileObject.h
 */

#ifndef MOBILEOBJECT_H
#define MOBILEOBJECT_H

#include "geologic-core/graphicTemplates/GeologicCustomizeObject.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "geologic-core/objects/dynamic/Trajectory.h"
#include "geologic-core/objects/dynamic/Displacement.h"
#include "geologic-core/superClasses/Metadata.h"


class MobileObject : public GeologicCustomizeObject {

    public:
        //*/ -------------------------------------------------
        MobileObject();
        virtual ~MobileObject();

        //*/ -------------------------------------------------
        std::unordered_map<std::string, Trajectory*> listTrajectories;
        std::vector<Displacement*> listDisplacements;
};

#endif // MOBILEOBJECT_H
