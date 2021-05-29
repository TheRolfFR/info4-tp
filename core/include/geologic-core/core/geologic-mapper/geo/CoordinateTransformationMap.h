/**
 * \file	CoordinateTransformationMap.h
 */

#ifndef CoordinateTransformationMap_H
#define CoordinateTransformationMap_H

#include <string>
#include <unordered_map>
#include <ogr_geometry.h>


class CoordinateTransformationMap {

    public:
        //*/ -------------------------------------------------
        CoordinateTransformationMap();
        virtual ~CoordinateTransformationMap();

        //*/ -------------------------------------------------
        std::unordered_map<std::string, OGRCoordinateTransformation*>* cooTraMap;
};

#endif // CoordinateTransformationMap_H
