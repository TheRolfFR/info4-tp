/**
 * \file	GeographicalObject.h
 */

#ifndef GEOGRAPHICALOBJECT_H
#define GEOGRAPHICALOBJECT_H

#include "ogr_geometry.h"
#include <string>


class GeographicalObject: public OGRPoint {

    public:
        //*/ -------------------------------------------------
        GeographicalObject();
        virtual ~GeographicalObject();

        GeographicalObject(double x, double y, double z=0.0);
        GeographicalObject(std::string name, double x, double y, double z=0.0);
        GeographicalObject(GeographicalObject* obj);
        GeographicalObject(OGRPoint* pt);
        GeographicalObject(std::string name, OGRPoint* pt);

        //*/ -------------------------------------------------
        std::string name;
};

#endif // GEOGRAPHICALOBJECT_H
