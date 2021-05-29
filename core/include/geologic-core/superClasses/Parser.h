/**
 * \file	Parser.h
 */

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <fstream>
#include "geologic-core/core/geologic-launcher/ShapefileReader.h"


class Parser {

    public:
        //*/ -------------------------------------------------
        Parser();
        virtual ~Parser();

        //*/ -------------------------------------------------
        virtual void parse(std::string pathName, std::string additionalInformations) = 0;
        virtual void parseShp(std::string pathName, OGRSpatialReference* csOrigin, OGRSpatialReference* csDestination) = 0;

        //*/ -------------------------------------------------
        ShapefileReader* shapefileReader;
};

#endif // PARSER_H
