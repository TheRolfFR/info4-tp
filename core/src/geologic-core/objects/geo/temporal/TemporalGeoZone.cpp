/**
 * \file	TemporalGeoZone.cpp
 * \class	TemporalGeoZone
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of TemporalGeoZone object
 *
 * \details Methods of TemporalGeoZone object
 * A TemporalGeoZone represents a GeoZone in the time dimension. It inherits from TemporalGeoData (for the timestamp)
 * It actually links the address of a GeoZone with a timestamp
 */

#include "geologic-core/objects/geo/temporal/TemporalGeoZone.h"

using namespace std;


/**
 * \brief 	Default constructor of class TemporalGeoZone
 *
 * \param 	None
 * \return 	None
 *
 * The GeoZone address is set to nullptr, the timestamp is set to 0, tag is set to ["type"] = "undefined"
 */
TemporalGeoZone::TemporalGeoZone() {
    this->zone = nullptr;
    this->timestamp = 0;
}

/**
 * \brief 	Default destructor of class TemporalGeoZone
 *
 * \param 	None
 * \return 	None
 */
TemporalGeoZone::~TemporalGeoZone() {
    this->zone = nullptr;
    this->timestamp = 0;
}

/**
 * \brief 	Constructor with parameters of class TemporalGeoZone
 *
 * \param 	zone        The address of the GeoZone to set in the time dimension
 * \param   timestamp   Date and time of this TemporalGeoZone
 * \return 	None
 */
TemporalGeoZone::TemporalGeoZone(GeoZone* zone, time_t timestamp) {
    this->zone = zone;
    this->timestamp = timestamp;
}
