/**
 * \file	TemporalGeoPoint.cpp
 * \class	TemporalGeoPoint
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of TemporalGeoPoint object
 *
 * Methods of TemporalGeoPoint object
 * A TemporalGeoPoint represents a GeoPoint in the time dimension. It inherits from TemporalGeologicGeometricalObject (for the timestamp) and from GeoPoint (for the position)
 */

#include "geologic-core/objects/geo/temporal/TemporalGeoPoint.h"

using namespace std;


/**
 * \brief 	Default constructor of class TemporalGeoPoint
 *
 * \param 	None
 * \return 	None
 *
 * The timestamp and position are set to 0, the CoordinateSystem is set to nullptr, tag is set to ["type"] = "undefined"
 */
TemporalGeoPoint::TemporalGeoPoint() {
    this->timestamp = 0;
}

/**
 * \brief 	Default destructor of class TemporalGeoPoint
 *
 * \param 	None
 * \return 	None
 */
TemporalGeoPoint::~TemporalGeoPoint() {
    this->timestamp = 0;
}

/**
 * \brief 	Constructor with parameters of class TemporalGeoPoint
 *
 * \param   timestamp   Date and time of this TemporalGeoPoint
 * \return 	None
 *
 * The position is set to 0, the CoordinateSystem is set to nullptr
 */
TemporalGeoPoint::TemporalGeoPoint(double timestamp) {
    this->timestamp = timestamp;
}

/**
 * \brief 	Constructor with parameters of class TemporalGeoPoint
 *
 * \param   x           Position in the X axis
 * \param   y           Position in the Y axis
 * \param   z           Position in the Z axis
 * \param   timestamp   Date and time of this TemporalGeoPoint
 * \return 	None
 *
 * The CoordinateSystem is set to nullptr
 */
TemporalGeoPoint::TemporalGeoPoint(double x, double y, double z, double timestamp) {
    this->timestamp = timestamp;
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

/**
 * \brief 	Constructor with parameters of class TemporalGeoPoint
 *
 * \param   point       The address of the GeoPoint to set in the time dimension
 * \param   timestamp   Date and time of this TemporalGeoPoint
 * \return 	None
 *
 * \details The values of the GeoPoint are actually copied
 */
TemporalGeoPoint::TemporalGeoPoint(OGRPoint* point, double timestamp) {
    this->timestamp = timestamp;
    this->setX(point->getX());
    this->setY(point->getY());
    this->setZ(point->getZ());
}

/**
 * \brief 	Copy constructor of class TemporalGeoPoint
 *
 * \param   point       The address of the TemporalGeoPoint to set in the time dimension
 * \return 	None
 *
 * The values of the TemporalGeoPoint are actually copied
 */
TemporalGeoPoint::TemporalGeoPoint(TemporalGeoPoint* point) {
    this->timestamp = point->timestamp;
    this->setX(point->getX());
    this->setY(point->getY());
    this->setZ(point->getZ());

    std::unordered_map<std::string, std::string>::iterator it = point->listTags.begin();
    for (; it!=point->listTags.end(); it++) {
        this->listTags.insert(std::pair<std::string, std::string>(it->first, it->second));
    }
}
