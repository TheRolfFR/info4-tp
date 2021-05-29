/**
 * \file	TransportationType.h
 */

#ifndef TRANSPORTATIONTYPE_H
#define TRANSPORTATIONTYPE_H

#include <string>
#include <vector>


class TransportationType {

    public:
        //*/ -------------------------------------------------
        TransportationType();
        virtual ~TransportationType();

        TransportationType(TransportationType* transportationType);
        TransportationType(std::string typeId, std::string typeDescription);

        //*/ -------------------------------------------------
        std::string typeId;
        std::string typeDescription;
        std::vector<std::string> parents;
        std::vector<std::string> subMeans;
        float averageSpeed;
};

#endif // TRANSPORTATIONTYPE_H
