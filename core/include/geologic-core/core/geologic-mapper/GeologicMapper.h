/**
 * \file	GeologicMapper.h
 */

#ifndef GEOLOGICMAPPER_H
#define GEOLOGICMAPPER_H

#include "geologic-core/superClasses/Mapper.h"
#include "geologic-core/core/geologic-mapper/social/IndividualMap.h"
#include "geologic-core/core/geologic-mapper/transportation/TransportationTypeMap.h"
#include "geologic-core/core/geologic-mapper/geo/GeoZoneHierarchyMap.h"


class GeologicMapper : public Mapper {

    public:
        //*/ -------------------------------------------------
        static GeologicMapper* getInstance();

        //*/ -------------------------------------------------
        IndividualMap*          indMapper;
        TransportationTypeMap*  traTypMapper;
        GeoZoneHierarchyMap*    geoZonHieMapper;

    private:
        //*/ -------------------------------------------------
        GeologicMapper();
        ~GeologicMapper();

        //*/ -------------------------------------------------
        GeologicMapper(GeologicMapper const&) = delete;
        void operator = (GeologicMapper const&) = delete;

        //*/ -------------------------------------------------
        static GeologicMapper* instance;
};

#endif // GEOLOGICMAPPER_H
