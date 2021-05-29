/**
 * \file	Trajectory.cpp
 * \class   Trajectory
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Trajectory object
 *
 * \details Methods of Trajectory object. A Trajectory represent the accurate movement in time and space of a MobileObject.
 * A Trajectory consists of a list of TemporalGeoPoint.
 */

#include "geologic-core/objects/dynamic/Trajectory.h"
#include "geologic-core/algorithms/trajectories/Bspline.h"

using namespace std;
using namespace customToolbox;


/**
 * \brief 	Default constructor of class Trajectory
 *
 * \param 	None
 * \return 	None
 */
Trajectory::Trajectory() {
    this->transportationType = nullptr;
    this->trajectory = new vector<TemporalGeoPoint*>();
    this->lastTrajectorySize = 0;
}

/**
 * \brief 	Default destructor of class Trajectory
 *
 * \param 	None
 * \return 	None
 */
Trajectory::~Trajectory() {
    vector<TemporalGeoPoint*>::iterator it = trajectory->begin();
    while (it != trajectory->end()) {
        if (*it != nullptr) delete(*it);
        *it = nullptr;
        it++;
    }
    this->trajectory->clear();
    delete(this->trajectory);
    this->trajectory = nullptr;
    this->lastTrajectorySize = 0;

    if (this->transportationType != nullptr) delete(this->transportationType);
    this->transportationType = nullptr;
}

/**
 * \brief 	Copy constructor of class Trajectory
 *
 * \param 	trajectory  The address of the Trajectory instance to copy
 * \return 	None
 *
 * This will create a deep copy of trajectory
 */
Trajectory::Trajectory(Trajectory* trajectory) {
    this->trajectory = new vector<TemporalGeoPoint*>();
    for (unsigned int i=0; i<trajectory->trajectory->size(); i++) {
        this->trajectory->push_back(new TemporalGeoPoint(trajectory->trajectory->at(i)));
    }

    this->transportationType = nullptr;
    if (trajectory->transportationType != nullptr) this->transportationType = new TransportationType(trajectory->transportationType);
    this->lastTrajectorySize = this->trajectory->size();
}

/**
 * \brief 	Constructor with parameters of class Trajectory
 *
 * \param 	trajectory            The address of a vector of TemporalGeoPoint
 * \param   transportationType    The TransportationType of the Trajectory
 * \return 	None
 *
 * The vector of TemporalGeoPoint and the transportation type will be copied
 */
Trajectory::Trajectory(std::vector<TemporalGeoPoint*>* trajectory, TransportationType* transportationType) {
    this->trajectory = new vector<TemporalGeoPoint*>();
    for (unsigned int i=0; i<trajectory->size(); i++) {
        this->trajectory->push_back(new TemporalGeoPoint(trajectory->at(i)));
    }

    this->transportationType = new TransportationType(transportationType);
    this->lastTrajectorySize = this->trajectory->size();
}

/**
 * \brief 	Adds a TemporalGeoPoint to the trajectory vector
 *
 * \param 	position    The address of the TemporalGeoPoint to add
 * \return 	None
 *
 * This will create a deep copy of position
 */
void Trajectory::addPosition(TemporalGeoPoint* position) {
    this->trajectory->push_back(new TemporalGeoPoint(position));
    // do NOT add this->lastTrajectorySize = this->trajectory->size();
}

/**
 * \brief 	Inserts a TemporalGeoPoint to the trajectory vector at the rigth time
 *
 * \param 	position    The address of the TemporalGeoPoint to add
 * \return 	None
 *
 * This will create a deep copy of position
 */
void Trajectory::insertPosition(TemporalGeoPoint* position) {
    double timestamp = position->timestamp;
    TemporalGeoPoint* firstPoint = this->trajectory->front();
    TemporalGeoPoint* lastPoint = this->trajectory->back();
    TemporalGeoPoint* currentPoint = firstPoint;

    if (timestamp < firstPoint->timestamp || timestamp > lastPoint->timestamp) return;
    vector<TemporalGeoPoint*>::iterator it = trajectory->begin();
    for (; it!= trajectory->end(); it++) {
        currentPoint = *it;
        if (currentPoint->timestamp >= timestamp && firstPoint->timestamp < timestamp) {
            trajectory->insert(it, new TemporalGeoPoint(position));
            break;
        }
        firstPoint = currentPoint;
    }
}

/**
 * \brief 	Gets back the closest TemporalGeoPoint of the Trajectory from a specific timestamp
 *
 * \param 	timestamp   The double specified to get back the closets TemporalGeoPoint
 * \return 	The address of the closest TemporalGeoPoint from the timestamp
 */
std::unique_ptr<TemporalGeoPoint> Trajectory::getClosestPoint(double timestamp) {
    TemporalGeoPoint* firstPoint = this->trajectory->front();
    TemporalGeoPoint* lastPoint = this->trajectory->back();

    if (timestamp <= firstPoint->timestamp) return make_unique<TemporalGeoPoint>(firstPoint);
    if (timestamp >= lastPoint->timestamp) return make_unique<TemporalGeoPoint>(lastPoint);

    TemporalGeoPoint* returnPoint = firstPoint;
    double minTemp = abs(timestamp - returnPoint->timestamp);
    for (unsigned int i=1; i<this->trajectory->size(); i++) {
        TemporalGeoPoint* tmp = this->trajectory->at(i);
        double tmpTemp = abs(timestamp - tmp->timestamp);
        if (tmpTemp == 0) return make_unique<TemporalGeoPoint>(tmp);
        if (tmpTemp <= minTemp) {
            minTemp = tmpTemp;
            returnPoint = tmp;
        }
    }
    return make_unique<TemporalGeoPoint>(returnPoint);
}

/**
 * \brief 	Returns a new TemporalGeoPoint from a specific timestamp according to the trajectory list
 *
 * \param 	timestamp   The double specified to get back the new TemporalGeoPoint
 * \return 	The address of a new TemporalGeoPoint
 *
 * Returns the address of a new TemporalGeoPoint if possible. nullptr otherwise.
 */
unique_ptr<TemporalGeoPoint> Trajectory::getNewPositionAt(double timestamp) {
    TemporalGeoPoint* firstPoint = this->trajectory->front();
    TemporalGeoPoint* lastPoint = this->trajectory->back();

    if (timestamp <= firstPoint->timestamp) return make_unique<TemporalGeoPoint>(firstPoint);
    if (timestamp >= lastPoint->timestamp) return make_unique<TemporalGeoPoint>(lastPoint);

    for (unsigned int i=0; i<this->trajectory->size()-1; i++) {
        TemporalGeoPoint* p0 = this->trajectory->at(i);
        TemporalGeoPoint* p1 = this->trajectory->at(i+1);

        if (p0->timestamp <= timestamp && timestamp < p1->timestamp) {
            // le nouveau point va être sur ce segment
            //on calcule la proportion
            double durationp0p1 = p1->timestamp - p0->timestamp;
            double durationp0t = timestamp - p0->timestamp;
            double coeff = durationp0t*1.0/durationp0p1;

            //et on reporte cette proportion sur la distance
            double posX = p0->getX() + coeff*(p1->getX()-p0->getX());
            double posY = p0->getY() + coeff*(p1->getY()-p0->getY());
            pair<string, string> tag = pair<string, string>("type", "Intermediate position on trajectory");
            return (make_unique<TemporalGeoPoint>(posX, posY, 0.0, timestamp));
        }
    }
    return nullptr;
}

/**
 * \brief 	Returns information on whether the Trajectory size has changed
 *
 * \param 	None
 * \return 	true if the Trajectory size has changed since last call, false otherwise
 */
bool Trajectory::hasChanged() {
    if (this->trajectory->size() != this->lastTrajectorySize) {
        this->lastTrajectorySize = this->trajectory->size();
        return true;
    }
    return false;
}

/**
 * \brief 	Returns display information to the caller
 *
 * \param 	timestamp   The current display time
 * \return 	The position of the MobileObject actor of this Trajectory at timestamp, nullptr if the Trajectory can't be displayed at timestamp
 *
 * /!\ Attention /!\ The returned OGRPoint will have to be deleted by the caller
 */
unique_ptr<OGRPoint> Trajectory::display(double timestamp) {

    TemporalGeoPoint* firstPoint = this->trajectory->front();
    TemporalGeoPoint* lastPoint = this->trajectory->back();
    if ((timestamp < firstPoint->timestamp) || (timestamp > lastPoint->timestamp)) return nullptr;
    return computeDisplayPoint(timestamp, this);
}

/**
 * \brief 	Returns display information to the caller
 *
 * \param 	timestamp   The current display time
 * \param   splineOrder The order of the B-spline used for the approximation
 * \return 	The position of the MobileObject actor of this Trajectory at timestamp, nullptr if the Trajectory can't be displayed at timestamp
 *
 * /!\ Attention /!\ The returned OGRPoint will have to be deleted by the caller
 */
unique_ptr<OGRPoint> Trajectory::display(double timestamp, int splineOrder) {

    TemporalGeoPoint* firstPoint = this->trajectory->front();
    TemporalGeoPoint* lastPoint = this->trajectory->back();
    if ((timestamp < firstPoint->timestamp) || (timestamp > lastPoint->timestamp)) return nullptr;

    string approximationAlgorithmName = "B-spline";
    Trajectory* approximationTrajectory = nullptr;
    bool cache = this->mapCacheTrajectories.find(approximationAlgorithmName) != this->mapCacheTrajectories.end();
    if (!cache || (cache && this->hasChanged())) {
        approximationTrajectory = this->bsplineModule->computeBsplineTrajectory(this, splineOrder).release();
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
 * \return 	The position of the MobileObject actor of this Trajectory at timestamp, nullptr if the Trajectory can't be displayed at timestamp
 *
 * /!\ Attention /!\ The returned OGRPoint will have to be deleted by the caller
 */
unique_ptr<OGRPoint> Trajectory::display(double timestamp, std::string approximationAlgorithmName, double factor) {

    TemporalGeoPoint* firstPoint = this->trajectory->front();
    TemporalGeoPoint* lastPoint = this->trajectory->back();
    if ((timestamp < firstPoint->timestamp) || (timestamp > lastPoint->timestamp)) return nullptr;

    Trajectory* approximationTrajectory = nullptr;
    bool cache = this->mapCacheTrajectories.find(approximationAlgorithmName) != this->mapCacheTrajectories.end();
    if (!cache || (cache && this->hasChanged())) {
        if (approximationAlgorithmName == "Gravity-like") {
            approximationTrajectory = bsplineModule->computeGravityLikeModelTrajectory(this, factor).release();
        } else if (approximationAlgorithmName == "Smoothed B-spline") {
            approximationTrajectory = bsplineModule->computeSmoothedBsplineTrajectory(this, factor).release();
        } else if (approximationAlgorithmName == "Fixed B-spline rounded") {
            approximationTrajectory = bsplineModule->computeFixedBsplineRoundedModelTrajectory(this, factor).release();
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
 * \return 	The position of the MobileObject actor of this Trajectory at timestamp, nullptr if the Trajectory can't be displayed at timestamp
 *
 * /!\ Attention /!\ The returned OGRPoint will have to be deleted by the caller
 */
unique_ptr<OGRPoint> Trajectory::display(double timestamp, std::unordered_map<std::string, GeoZone*>* zones) {

    TemporalGeoPoint* firstPoint = this->trajectory->front();
    TemporalGeoPoint* lastPoint = this->trajectory->back();
    if ((timestamp < firstPoint->timestamp) || (timestamp > lastPoint->timestamp)) return nullptr;

    string approximationAlgorithmName = "Automatic B-spline rounded";
    Trajectory* approximationTrajectory = nullptr;
    bool cache = this->mapCacheTrajectories.find(approximationAlgorithmName) != this->mapCacheTrajectories.end();
    if (!cache || (cache && this->hasChanged())) {
        approximationTrajectory = bsplineModule->computeAutomaticBsplineRoundedModelTrajectory(this, zones).release();
        this->mapCacheTrajectories.insert(pair<string, Trajectory*>(approximationAlgorithmName, std::move(approximationTrajectory)));
    }
    approximationTrajectory = this->mapCacheTrajectories.at(approximationAlgorithmName);
    return computeDisplayPoint(timestamp, approximationTrajectory);
}

/**
 * \brief 	Computes the position of a point to display (used by the previous methods)
 *
 * \param 	timestamp   The current display time
 * \param   approximationTrajectory The trajectory to use to extract the OGRPoint at timestamp
 * \return 	The position of the MobileObject actor of this Trajectory at timestamp, nullptr if the Trajectory can't be displayed at timestamp
 *
 * /!\ Attention /!\ The returned OGRPoint will have to be deleted by the caller
 */
unique_ptr<OGRPoint> Trajectory::computeDisplayPoint(double timestamp, Trajectory* approximationTrajectory) {
    bool found = false;
    double posX = 0.0;
    double posY = 0.0;
    for (unsigned int i=0; i<approximationTrajectory->trajectory->size()-1; i++) {
        TemporalGeoPoint* p0 = approximationTrajectory->trajectory->at(i);
        TemporalGeoPoint* p1 = approximationTrajectory->trajectory->at(i+1);

        if (p0->timestamp <= timestamp && timestamp < p1->timestamp) {
            // le nouveau point va etre sur ce segment
            //on calcule la proportion
            double durationp0p1 = p1->timestamp - p0->timestamp;
            double durationp0t = timestamp - p0->timestamp;
            double coeff = durationp0t/durationp0p1;
            //cout << "Test: " << p0->timestamp << " / " << timestamp << " / " << p1->timestamp << " : " << coeff << endl;

            //et on reporte cette proportion sur la distance
            posX = p0->getX() + coeff*(p1->getX()-p0->getX());
            posY = p0->getY() + coeff*(p1->getY()-p0->getY());
            found = true;
            break;
        }
    }

    if (found) {
        return (make_unique<OGRPoint>(posX, posY, 0.0));
    } else {
        TemporalGeoPoint* front = approximationTrajectory->trajectory->front();
        if(timestamp < front->timestamp) { 
            return (make_unique<OGRPoint>(front->getX(), front->getY(), 0.0));
        }
        TemporalGeoPoint* back = approximationTrajectory->trajectory->back();
        if(timestamp >= back->timestamp) {
            return (make_unique<OGRPoint>(back->getX(), back->getY(), 0.0));
        }
    }
    return nullptr;
}

/**
 * \brief 	Copy constructor of class Trajectory
 *
 * \param 	trajectory  The address of the Trajectory instance to copy
 * \return 	None
 *
 * This will create a deep copy of trajectory
 */
void Trajectory::dummyFill(int slotDuration) {
    if (this->trajectory->size() > 1) {
        TemporalGeoPoint* lastPoint = this->trajectory->front();
        for (unsigned int i=1; i<this->trajectory->size(); i++) {
            this->trajectory->at(i)->timestamp = lastPoint->timestamp + slotDuration;
            lastPoint = this->trajectory->at(i);
        }
    }
}

/**
 * \brief 	Copy constructor of class Trajectory
 *
 * \param 	trajectory  The address of the Trajectory instance to copy
 * \return 	None
 *
 * This will create a deep copy of trajectory
 */
unsigned int Trajectory::size() {
    return this->trajectory->size();
}

/**
 * \brief 	Default destructor of class Trajectory
 *
 * \param 	None
 * \return 	None
 */
void Trajectory::clear(bool hard) {
    if (hard) {
        for (unsigned int i=0; i<this->trajectory->size(); i++) {
            if (this->trajectory->at(i) != nullptr) delete(this->trajectory->at(i));
            this->trajectory->at(i) = nullptr;
        }
    }
    this->trajectory->clear();
}
