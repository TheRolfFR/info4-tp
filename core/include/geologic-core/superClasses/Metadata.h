/**
* \file     Metadata.h
*/

#ifndef METADATA_H
#define METADATA_H

#include <string>
#include <unordered_map>
#include <iostream>


class Metadata {

    public:
        //*/ -------------------------------------------------
        Metadata();
        virtual ~Metadata();

        //*/ -------------------------------------------------
        virtual void printDetails(std::unordered_map<std::string, std::string>* mapper=nullptr) = 0;
        virtual std::string details(std::unordered_map<std::string, std::string>* mapper=nullptr) = 0;

        //*/ -------------------------------------------------
        std::string metadataName;
};

#endif // METADATA_H
