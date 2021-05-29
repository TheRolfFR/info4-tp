/**
 * \file	Individual.h
 */

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "geologic-core/objects/dynamic/MobileObject.h"
#include "geologic-core/objects/geo/untemporal/GeographicalObject.h"


class Individual : public MobileObject, public GeographicalObject {

    public:
        //*/ -------------------------------------------------
        Individual(std::string Identity);
        virtual ~Individual();

        //*/ -------------------------------------------------
        std::string Identity;
        std::string IMEI;
};

#endif // INDIVIDUAL_H
