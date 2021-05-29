/**
 * \file	IndividualMap.h
 */

#ifndef INDIVIDUALMAP_H
#define INDIVIDUALMAP_H

#include <unordered_map>
#include <string>
#include "geologic-core/objects/social/Individual.h"


class IndividualMap {

    public:
        //*/ -------------------------------------------------
        IndividualMap();
        virtual ~IndividualMap();

        //*/ -------------------------------------------------
        std::unordered_map<std::string, Individual*>* indMap;
};

#endif // INDIVIDUALMAP_H
