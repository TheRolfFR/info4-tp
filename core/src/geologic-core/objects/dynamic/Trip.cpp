/**
 * \file	Trip.cpp
 * \class   Trip
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Trip object
 *
 * \details Methods of Trip object. A Trip represents the movement at a specific time of a MobileObject from a GeoZone of origin to a GeoZone of destination with a
 * specific TransportationType.
 */

#include "geologic-core/objects/dynamic/Trip.h"

using namespace std;


/**
 * \brief 	Default constructor of class Trip
 *
 * \param 	None
 * \return 	None
 */
Trip::Trip() {
    this->zoneOrigin = nullptr;
    this->zoneDestination = nullptr;
    this->type = nullptr;
    this->tripDuration = 0;
}

/**
 * \brief 	Default destructor of class Trip
 *
 * \param 	None
 * \return 	None
 */
Trip::~Trip() {
    this->zoneOrigin = nullptr;
    this->zoneDestination = nullptr;
    this->type = nullptr;
    this->tripDuration = 0;

    //do NOT touch listMetadata
}

/**
 * \brief 	Copy constructor of class Trip
 *
 * \param 	trip    The address of the Trip to copy
 * \return 	None
 *
 * This will create a deep copy of trip
 */
Trip::Trip(Trip* trip) {
    this->zoneOrigin = trip->zoneOrigin;
    this->zoneDestination = trip->zoneDestination;
    this->type = trip->type;
    this->tripDuration = trip->tripDuration;
    this->listMetadata = trip->listMetadata;
}

/**
 * \brief 	Constructor with parameters of class Trip
 *
 * \param 	zoneOrigin      The address of the origin TemporalGeoZone of this Trip
 * \param   zoneDestination The address of the destination TemporalGeoZone of this Trip
 * \param   type            The address of the TransportationType of this Trip
 * \return 	None
 */
Trip::Trip(TemporalGeoZone* zoneOrigin, TemporalGeoZone* zoneDestination, TransportationType* type) {
    this->zoneOrigin = zoneOrigin;
    this->zoneDestination = zoneDestination;
    this->type = type;
    this->tripDuration = this->zoneDestination->timestamp - this->zoneOrigin->timestamp;
}

/**
 * \brief 	Computes the duration of the Trip
 *
 * \param 	None
 * \return 	None
 */
void Trip::computeDuration() {
    this->tripDuration = this->zoneDestination->timestamp - this->zoneOrigin->timestamp;
}

/**
 * \brief 	Prints the details of the Trip
 *
 * \param 	None
 * \return 	None
 *
 * /// TODO check real usage
 */
void Trip::printTrip() {
    std::cout << "Trip: " << std::endl;
}

/**
 * \brief 	Returns display information to the caller
 *
 * \param 	timestamp   The current display time
 * \return 	The position of the MobileObject actor of this Trip at timestamp, nullptr if the Trip can't be displayed at timestamp
 *
 * /!\ Attention /!\ The returned OGRPoint will have to be deleted by the caller
 */
std::unique_ptr<OGRPoint> Trip::display(double timestamp) {
    if ((timestamp <= this->zoneOrigin->timestamp) || (timestamp >= this->zoneDestination->timestamp)) return nullptr;

    double timeCoeff = (timestamp - this->zoneOrigin->timestamp) / (this->zoneDestination->timestamp - this->zoneOrigin->timestamp);
    double deltaX = (this->zoneDestination->zone->getX() - this->zoneOrigin->zone->getX());
    double deltaY = (this->zoneDestination->zone->getY() - this->zoneOrigin->zone->getY());

    double posX = this->zoneOrigin->zone->getX() + timeCoeff*deltaX;
    double posY = this->zoneOrigin->zone->getY() + timeCoeff*deltaY;

    return (make_unique<OGRPoint>(posX, posY, 0));
}

/**
 * \brief 	Returns display information to the caller
 *
 * /// TODO check real usage
 */
std::unique_ptr<OGRPoint> Trip::display(double timestamp, int splineOrder __attribute__((unused))) {
    return this->display(timestamp);
}

/**
 * \brief 	Returns display information to the caller
 *
 * /// TODO check real usage
 */
std::unique_ptr<OGRPoint> Trip::display(double timestamp, std::string approximationAlgorithmName __attribute__((unused)), double factor __attribute__((unused))) {
    return this->display(timestamp);
}

/**
 * \brief 	Returns display information to the caller
 *
 * /// TODO check real usage
 */
std::unique_ptr<OGRPoint> Trip::display(double timestamp, std::unordered_map<std::string, GeoZone*>* zones __attribute__((unused))) {
    return this->display(timestamp);
}
