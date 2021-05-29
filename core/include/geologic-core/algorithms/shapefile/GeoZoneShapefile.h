/**
 * \file	GeoZoneShapefile.h
 */

#ifndef GEOZONESHAPEFILE_H
#define GEOZONESHAPEFILE_H

#include "geologic-core/objects/geo/untemporal/GeoZone.h"

class GeoZoneShapefile : public GeoZone {

    public:
        //*/ -------------------------------------------------
        GeoZoneShapefile();
        virtual ~GeoZoneShapefile();

        GeoZoneShapefile(int type);

        //*/ -------------------------------------------------
        void setShapefileType(int type);

        //*/ -------------------------------------------------
        std::vector<int> parts;
        std::vector<int> partTypes;
        std::vector<double> zarray;
        std::vector<double> marray;
        int shapefileType;
        double zmin;
        double zmax;
        double mvalue;
};

#endif // GEOZONESHAPEFILE_H
