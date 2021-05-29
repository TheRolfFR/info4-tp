/**
 * \file	Displacement.cpp
 * \class   Displacement
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Displacement object
 *
 * \details Methods of Displacement object. A Displacement represents the displacement of a MobileObject in time and space, it associate
 * a reason to a particular displacement. A Displacement consists of a list of Trip done to achieve this displacement.
 */

#include "geologic-core/objects/dynamic/Displacement.h"
#include "geologic-core/objects/dynamic/Trajectory.h"
#include "geologic-core/algorithms/trajectories/Bspline.h"

using namespace std;
using namespace customToolbox;


/**
 * \brief 	Default constructor of class Displacement
 *
 * \param 	None
 * \return 	None
 */
Displacement::Displacement() {
    this->zoneOrigin = nullptr;
    this->zoneDestination = nullptr;
    this->displacementDuration = 0;
    this->mainReason = "";
    this->lastTripsSize = 0;
}

/**
 * \brief 	Default destructor of class Displacement
 *
 * \param 	None
 * \return 	None
 */
Displacement::~Displacement() {
    this->mainReason = "";

    for (unsigned int i=0; i<this->trips.size(); i++) {
        if (this->trips[i] != nullptr) delete(this->trips[i]);
        this->trips[i] = nullptr;
    }
    this->trips.clear();
    this->lastTripsSize = 0;
}

/**
 * \brief 	Copy constructor of class Displacement
 *
 * \param 	displacement    The address of the Displacement object to copy
 * \return 	None
 *
 * This will create a deep copy of displacement
 */
Displacement::Displacement(Displacement* displacement) {
    this->zoneOrigin = displacement->zoneOrigin;
    this->zoneDestination = displacement->zoneDestination;
    this->displacementDuration = displacement->displacementDuration;
    this->mainReason = displacement->mainReason;

    for (unsigned int i=0; i<displacement->trips.size(); i++) {
        Trip* trip = new Trip(displacement->trips[i]);
        this->trips.push_back(trip);
    }
    this->lastTripsSize = this->trips.size();
}

/**
 * \brief 	Constructor with parameters of class Displacement
 *
 * \param 	zoneOrigin      The address of the origin TemporalGeoZone of this Displacement
 * \param   zoneDestination The address of the destination TemporalGeoZone of this Displacement
 * \param   reason          The main reason of this Displacement
 * \return 	None
 */
Displacement::Displacement(TemporalGeoZone* zoneOrigin, TemporalGeoZone* zoneDestination, std::string reason) {
    this->zoneOrigin = zoneOrigin;
    this->zoneDestination = zoneDestination;
    this->displacementDuration = (this->zoneDestination->timestamp - this->zoneOrigin->timestamp);
    this->mainReason = reason;
}

/**
 * \brief 	Returns information on whether the Trip list size has changed
 *
 * \param 	None
 * \return 	true if the Trip list size has changed since last call, false otherwise
 */
bool Displacement::hasChanged() {
    if (this->trips.size() != this->lastTripsSize) {
        this->lastTripsSize = this->trips.size();
        return true;
    }
    return false;
}

/**
 * \brief 	Returns display information to the caller
 *
 * \param 	timestamp   The current display time
 * \return 	The position of the MobileObject actor of this Displacement at timestamp, nullptr if the Displacement can't be displayed at timestamp
 *
 * /!\ Important /!\ The returned OGRPoint will have to be deleted by the caller
 */
unique_ptr<OGRPoint> Displacement::display(double timestamp) {

    TemporalGeoZone* p0 = this->zoneOrigin;
    TemporalGeoZone* p1 = this->zoneDestination;
    if ((timestamp <= p0->timestamp) || (timestamp >= p1->timestamp)) return nullptr;

    if (this->trips.size() > 0) {
        bool found = false;
        int i = 0;
        while (!found) {
            p0 = this->trips[i]->zoneOrigin;
            p1 = this->trips[i]->zoneDestination;
            if ((timestamp >= p0->timestamp) && (timestamp <= p1->timestamp)) found = true;
            i++;
        }
    }

    double timeCoeff = (timestamp - p0->timestamp) / (p1->timestamp - p0->timestamp);
    double posX = p0->zone->getX() + timeCoeff*(p1->zone->getX() - p0->zone->getX());
    double posY = p1->zone->getY() + timeCoeff*(p1->zone->getY() - p0->zone->getY());

    return (make_unique<OGRPoint>(posX, posY, 0));
}

/**
 * \brief 	Returns display information to the caller
 *
 * \param 	timestamp   The current display time
 * \param   splineOrder The order of the B-spline used for the approximation
 * \return 	The position of the MobileObject actor of this Displacement at timestamp, nullptr if the Displacement can't be displayed at timestamp
 *
 * /!\ Important /!\ The returned OGRPoint will have to be deleted by the caller
 */
std::unique_ptr<OGRPoint> Displacement::display(double timestamp, int splineOrder) {

    TemporalGeoZone* p0 = this->zoneOrigin;
    TemporalGeoZone* p1 = this->zoneDestination;
    if ((timestamp <= p0->timestamp) || (timestamp >= p1->timestamp)) return nullptr;

    string approximationAlgorithmName = "B-spline";
    Trajectory* approximationTrajectory = nullptr;
    bool cache = this->mapCacheTrajectories.find(approximationAlgorithmName) != this->mapCacheTrajectories.end();
    if (!cache || (cache && this->hasChanged())) {

        unique_ptr<Trajectory> trajectory = make_unique<Trajectory>();
        for (unsigned int i=0; i<this->trips.size(); i++) {
            Trip* currentTrip = this->trips[i];

            std::pair<std::string, std::string> tag = std::pair<std::string, std::string>("type", "temp Pos displacement");
            TemporalGeoPoint tmpPos = TemporalGeoPoint(currentTrip->zoneOrigin->zone, currentTrip->zoneOrigin->timestamp);
            trajectory->addPosition(&tmpPos);

            if (i >= this->trips.size()) {
                TemporalGeoPoint tmpPosEnd = TemporalGeoPoint(currentTrip->zoneDestination->zone, currentTrip->zoneDestination->timestamp);
                trajectory->addPosition(&tmpPosEnd);
            }
        }

        approximationTrajectory = this->bsplineModule->computeBsplineTrajectory(trajectory.get(), splineOrder).release();
        this->mapCacheTrajectories.insert(pair<string, Trajectory*>(approximationAlgorithmName, std::move(approximationTrajectory)));
    }
    approximationTrajectory = this->mapCacheTrajectories.at(approximationAlgorithmName);
    return computeDisplayPoint(timestamp, approximationTrajectory);
}

/**
 * \brief 	Returns display information to the caller
 *
 * \param 	timestamp                   The current display time
 * \param   approximationAlgorithmName  The approximation algorithm to use
 * \param   factor                      The factor used for the approximation
 * \return 	The position of the MobileObject actor of this Displacement at timestamp, nullptr if the Displacement can't be displayed at timestamp
 *
 * /!\ Important /!\ The returned OGRPoint will have to be deleted by the caller
 * the approximationAlgorithmName are (Gravity-like, Smoothed B-spline, Fixed B-spline rounded)
 */
std::unique_ptr<OGRPoint> Displacement::display(double timestamp, std::string approximationAlgorithmName, double factor) {

    TemporalGeoZone* p0 = this->zoneOrigin;
    TemporalGeoZone* p1 = this->zoneDestination;
    if ((timestamp <= p0->timestamp) || (timestamp >= p1->timestamp)) return nullptr;

    Trajectory* approximationTrajectory = nullptr;
    bool cache = this->mapCacheTrajectories.find(approximationAlgorithmName) != this->mapCacheTrajectories.end();
    if (!cache || (cache && this->hasChanged())) {

        unique_ptr<Trajectory> trajectory = make_unique<Trajectory>();
        for (unsigned int i=0; i<this->trips.size(); i++) {
            Trip* currentTrip = this->trips[i];

            std::pair<std::string, std::string> tag = std::pair<std::string, std::string>("type", "temp Pos displacement");
            TemporalGeoPoint tmpPos = TemporalGeoPoint(currentTrip->zoneOrigin->zone, currentTrip->zoneOrigin->timestamp);
            trajectory->addPosition(&tmpPos);

            if (i >= this->trips.size()) {
                TemporalGeoPoint tmpPosEnd = TemporalGeoPoint(currentTrip->zoneDestination->zone, currentTrip->zoneDestination->timestamp);
                trajectory->addPosition(&tmpPosEnd);
            }
        }

        if (approximationAlgorithmName == "Gravity-like") {
            approximationTrajectory = this->bsplineModule->computeGravityLikeModelTrajectory(trajectory.get(), factor).release();
        } else if (approximationAlgorithmName == "Smoothed B-spline") {
            approximationTrajectory = this->bsplineModule->computeSmoothedBsplineTrajectory(trajectory.get(), factor).release();
        } else if (approximationAlgorithmName == "Fixed B-spline rounded") {
            approximationTrajectory = this->bsplineModule->computeFixedBsplineRoundedModelTrajectory(trajectory.get(), factor).release();
        }
        this->mapCacheTrajectories.insert(pair<string, Trajectory*>(approximationAlgorithmName, std::move(approximationTrajectory)));
    }
    approximationTrajectory = this->mapCacheTrajectories.at(approximationAlgorithmName);
    return computeDisplayPoint(timestamp, approximationTrajectory);
}

/**
 * \brief 	Returns display information to the caller
 *
 * \param 	timestamp   The current display time
 * \param   zones       The address of the map of GeoZone used for the approximation algorithm
 * \return 	The position of the MobileObject actor of this Displacement at timestamp, nullptr if the Displacement can't be displayed at timestamp
 *
 * /!\ Important /!\ The returned OGRPoint will have to be deleted by the caller
 * The approximationAlgorithmName is called "Automatic B-spline rounded" here (not as a parameter)
 */
std::unique_ptr<OGRPoint> Displacement::display(double timestamp, std::unordered_map<std::string, GeoZone*>* zones) {

    TemporalGeoZone* p0 = this->zoneOrigin;
    TemporalGeoZone* p1 = this->zoneDestination;
    if ((timestamp <= p0->timestamp) || (timestamp >= p1->timestamp)) return nullptr;

    string approximationAlgorithmName = "Automatic B-spline rounded";
    Trajectory* approximationTrajectory = nullptr;
    bool cache = this->mapCacheTrajectories.find(approximationAlgorithmName) != this->mapCacheTrajectories.end();
    if (!cache || (cache && this->hasChanged())) {

        unique_ptr<Trajectory> trajectory = make_unique<Trajectory>();
        for (unsigned int i=0; i<this->trips.size(); i++) {
            Trip* currentTrip = this->trips[i];

            std::pair<std::string, std::string> tag = std::pair<std::string, std::string>("type", "temp Pos displacement");
            TemporalGeoPoint tmpPos = TemporalGeoPoint(currentTrip->zoneOrigin->zone, currentTrip->zoneOrigin->timestamp);
            trajectory->addPosition(&tmpPos);

            if (i >= this->trips.size()) {
                TemporalGeoPoint tmpPosEnd = TemporalGeoPoint(currentTrip->zoneDestination->zone, currentTrip->zoneDestination->timestamp);
                trajectory->addPosition(&tmpPosEnd);
            }
        }

        approximationTrajectory = this->bsplineModule->computeAutomaticBsplineRoundedModelTrajectory(trajectory.get(), zones).release();
        this->mapCacheTrajectories.insert(pair<string, Trajectory*>(approximationAlgorithmName, std::move(approximationTrajectory)));
    }
    approximationTrajectory = this->mapCacheTrajectories.at(approximationAlgorithmName);
    return computeDisplayPoint(timestamp, approximationTrajectory);
}

/**
 * \brief 	Computes the position of a point to display (Used by the previous methods)
 *
 * \param 	timestamp   The current display time
 * \param   approximationTrajectory The trajectory to use to extract the OGRPoint at timestamp
 * \return 	The position of the MobileObject actor of this Displacement at timestamp, nullptr if the Displacement can't be displayed at timestamp
 *
 * /!\ Important /!\ The returned OGRPoint will have to be deleted by the caller
 */
std::unique_ptr<OGRPoint> Displacement::computeDisplayPoint(double timestamp, Trajectory* approximationTrajectory) {
    bool found = false;
    double posX = 0.0;
    double posY = 0.0;

    for (unsigned int i=0; i<approximationTrajectory->trajectory->size()-1; i++) {
        TemporalGeoPoint* p0 = approximationTrajectory->trajectory->at(i);
        TemporalGeoPoint* p1 = approximationTrajectory->trajectory->at(i+1);

        if (p0->timestamp <= timestamp && timestamp < p1->timestamp) {
            // le nouveau point va être sur ce segment
            //on calcule la proportion
            double durationp0p1 = p1->timestamp - p0->timestamp;
            double durationp0t = timestamp - p0->timestamp;
            double coeff = durationp0t/durationp0p1;

            //et on reporte cette proportion sur la distance
            posX = p0->getX() + coeff*(p1->getX()-p0->getX());
            posY = p0->getY() + coeff*(p1->getY()-p0->getY());
            found = true;
            break;
        }
    }

    if (found) {
        return (make_unique<OGRPoint>(posX, posY, 0.0));
    }
    return nullptr;
}
