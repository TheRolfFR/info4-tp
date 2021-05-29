/**
 * \file	TemporalGeoData.cpp
 * \class	TemporalGeoData
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of TemporalGeoData object
 *
 * \details Methods of TemporalGeoData object
 * A TemporalGeoData object represents any object (GeoPoint, GeoZone) in the time dimension
 * It is a generic class and should not be used directly
 * It allows any object to access a timestamp (time_t)
 */

#include "geologic-core/objects/geo/temporal/TemporalGeoData.h"


/**
 * \brief 	Default constructor of class TemporalGeoData
 *
 * \param 	None
 * \return 	None
 */
TemporalGeoData::TemporalGeoData() {
    this->timestamp = 0;
}

/**
 * \brief 	Default destructor of class TemporalGeoData
 *
 * \param 	None
 * \return 	None
 */
TemporalGeoData::~TemporalGeoData() {
    this->timestamp = 0;
}

/**
 * \brief 	Returns display information to the caller
 *
 * \param 	None
 * \return 	true if the TemporalGeoData has to be displayed, false otherwise
 */
bool TemporalGeoData::display(double timestamp) {
    return (this->timestamp == timestamp);
}

/**
 * \brief 	Returns display information to the caller
 *
 * \param 	timestampOrigin         The starting display time
 * \param   timestampDestination    The ending display time
 * \return 	true if the TemporalGeoData has to be displayed, false otherwise
 */
bool TemporalGeoData::display(double timestampOrigin, double timestampDestination) {
    return (this->timestamp >= timestampOrigin && this->timestamp <= timestampDestination);
}
