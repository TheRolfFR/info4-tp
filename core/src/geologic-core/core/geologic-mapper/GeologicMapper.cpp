/**
 * \file	GeologicMapper.cpp
 * \class   GeologicMapper
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of GeologicMapper object
 *
 * \details This class is a container for maps of geologic-core object instances
 * Contains the references of maps holding CoordinateSystem, CoordinateTransformation, Individual, TransportationType, GeoZoneHierarchy
 */

#include "geologic-core/core/geologic-mapper/GeologicMapper.h"

GeologicMapper* GeologicMapper::instance = 0;


/**
 * \brief 	Default constructor of class GeologicMapper
 *
 * \param 	None
 * \return 	None
 */
GeologicMapper::GeologicMapper() {
    indMapper       = new IndividualMap();
    traTypMapper    = new TransportationTypeMap();
    geoZonHieMapper = new GeoZoneHierarchyMap();
}

/**
 * \brief 	Returns the instance of the GeologicMapper singleton
 *
 * \param 	None
 * \return 	The reference of the GeologicMapper singleton
 */
GeologicMapper* GeologicMapper::getInstance() {
    if (!instance) {
        instance = new GeologicMapper;
    }
    return instance;
}

/**
 * \brief 	Default destructor of class GeologicMapper
 *
 * \param 	None
 * \return 	None
 */
GeologicMapper::~GeologicMapper() {
    delete(indMapper);
    delete(traTypMapper);
    delete(geoZonHieMapper);

    indMapper       = nullptr;
    traTypMapper    = nullptr;
    geoZonHieMapper = nullptr;
}
