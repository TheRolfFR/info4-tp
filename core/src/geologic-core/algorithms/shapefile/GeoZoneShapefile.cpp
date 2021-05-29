/**
 * \file	GeoZoneShapefile.cpp
 * \class	GeoZoneShapefile
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Internal and temporary class used to create shapes while reading shapefile
 *
 * \details This class is creating temporary objects like shapes while reading a shapefile object. This class is not to be used by the final user.
 */

#include "geologic-core/algorithms/shapefile/GeoZoneShapefile.h"

using namespace std;


/**
 * \brief 	Default constructor of class GeoZoneShapefile
 *
 * \param 	None
 * \return 	None
 */
GeoZoneShapefile::GeoZoneShapefile() {
    this->shapefileType = 0;
    this->zmin = 0.0;
    this->zmax = 0.0;
    this->mvalue = 0.0;
}

/**
 * \brief 	Default destructor of class GeoZoneShapefile
 *
 * \param 	None
 * \return 	None
 */
GeoZoneShapefile::~GeoZoneShapefile() {}

/**
 * \brief 	Constructor with parameters of class GeoZoneShapefile
 *
 * \param 	shapefileType   the type of the shapefile
 * \return 	None
 *
 * The area is set to -1
 */
GeoZoneShapefile::GeoZoneShapefile(int shapefileType) {
    this->shapefileType = shapefileType;
    this->zmin = 0.0;
    this->zmax = 0.0;
    this->mvalue = 0.0;
}

/**
 * \brief 	Changes the shapefile type
 *
 * \param 	shapefileType   the type of the shapefile
 * \return 	None
 */
void GeoZoneShapefile::setShapefileType(int shapefileType) {
    this->shapefileType = shapefileType;
}
