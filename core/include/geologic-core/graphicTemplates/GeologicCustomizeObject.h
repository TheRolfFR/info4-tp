/**
 * \file	GeologicGraphicalObject.h
 */

#ifndef GEOLOGICCUSTOMIZEOBJECT_H
#define GEOLOGICCUSTOMIZEOBJECT_H

#include "geologic-core/superClasses/Metadata.h"
#include <unordered_map>
#include <string>
#include <vector>


class GeologicCustomizeObject {

    public:
        //*/ -------------------------------------------------
        GeologicCustomizeObject();
        virtual ~GeologicCustomizeObject();

        //*/ -------------------------------------------------
        std::vector<Metadata*> listMetadata;
        std::unordered_map<std::string, std::string> listTags;
};

#endif // GEOLOGICCUSTOMIZEOBJECT_H
