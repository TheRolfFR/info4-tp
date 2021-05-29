/**
 * \file	TransportationTypeMap.h
 */

#ifndef TRANSPORTATIONTYPEMAP_H
#define TRANSPORTATIONTYPEMAP_H

#include <string>
#include <unordered_map>
#include "geologic-core/objects/transportation/TransportationType.h"


class TransportationTypeMap {

    public:
        //*/ -------------------------------------------------
        TransportationTypeMap();
        virtual ~TransportationTypeMap();

        //*/ -------------------------------------------------
        std::unordered_map<std::string, TransportationType*>* traTypMap;
};

#endif // TRANSPORTATIONTYPEMAP_H
