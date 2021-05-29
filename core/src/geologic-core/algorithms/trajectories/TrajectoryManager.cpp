/**
 * \file	TrajectoryManager.cpp
 * \class   TrajectoryManager
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Contains main methods to manage Trajectory objects
 *
 * \details This class manages the Trajectory objects and propose several methods useful methods such as trajectory fill up, extraction of trips, etc.
 */

#include "geologic-core/algorithms/trajectories/TrajectoryManager.h"
#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"

using namespace std;
using namespace customToolbox;


/**
 * \brief 	Default constructor of class TrajectoryManager
 *
 * \param 	None
 * \return 	None
 */
TrajectoryManager::TrajectoryManager() {}

/**
 * \brief 	Default destructor of class TrajectoryManager
 *
 * \param 	None
 * \return 	None
 */
TrajectoryManager::~TrajectoryManager() {}

/**
 * \brief 	Fills a trajectory with interleaving TemporalGeoPoint such that the Trajectory represents one entire day without temporal "holes"
 *
 * \param 	trajectory      The Trajectory to fill
 * \param   slotDuration    The minimal time distance to keep between two TemporalGeoPoint (seconds)
 * \param   strategy        The strategy used to set the location of the interleaving TemporalGeoPoint
 * \return 	A new trajectory filled-up
 *
 * /!\ Important /!\ This does not modify the input Trajectory, the returned trajectory is a new instance and will have to be deleted by the caller.
 * The different strategies possibles are "first", "half", "last" and "custom_0.XX" where XX is a number. The slot duration is
 * expressed in seconds.
 */
unique_ptr<Trajectory> TrajectoryManager::dayFilling(Trajectory* trajectory, int slotDuration, std::string strategy) {

    unique_ptr<Trajectory> returnTrajectory = make_unique<Trajectory>();
    returnTrajectory->transportationType = NULL;

    TemporalGeoPoint startPointTmp = TemporalGeoPoint(trajectory->trajectory->front());
    startPointTmp.timestamp = lowerTimestamp(startPointTmp.timestamp, 24*60*60); //midnight
    TemporalGeoPoint endPointTmp = TemporalGeoPoint(trajectory->trajectory->back());
    endPointTmp.timestamp = lowerTimestamp(endPointTmp.timestamp, 24*60*60)+24*60*60; //midnight + 1day

    TemporalGeoPoint* lastPoint = &startPointTmp;
    TemporalGeoPoint* currentPoint = lastPoint;
    bool firstPointToCreate = true;

    for (unsigned int indTGP=0; indTGP<=trajectory->trajectory->size(); indTGP++) {

        if (indTGP >= trajectory->trajectory->size()) {
            currentPoint = &endPointTmp;
        } else {
            currentPoint = trajectory->trajectory->at(indTGP);
        }



        time_t currentGap = currentPoint->timestamp - lastPoint->timestamp;
        if (currentGap > slotDuration) {
            //on va calculer le nombre de TGP à insérer
            //toujours un nombre pair, et leur propre distance temporelle doit être inférieure à slotDuration
            double resDiv = ceil( (double) currentGap/ (double) slotDuration);
            unsigned int numberPointsToInsert = (unsigned int) resDiv;
            if (numberPointsToInsert%2 == 0) numberPointsToInsert++;
            time_t newGap = floor(currentGap/numberPointsToInsert);

            //on va donc rajouter (numberPointsToInsert-1) TGP
            for (unsigned int i=0; i<(numberPointsToInsert-1); i++) {
                TemporalGeoPoint* copyPoint = lastPoint;

                if (strategy == "first") {
                } else if (strategy == "last") {
                    copyPoint = currentPoint;
                } else if (strategy == "half") {
                    if (i >= (numberPointsToInsert-1)*0.5) {
                        copyPoint = currentPoint;
                    }
                } else if (split(strategy, '_')[0] == "custom") {
                    double coeff = atof((split(strategy, '_')[1]).c_str());
                    if (i >= (numberPointsToInsert-1)*coeff) {
                        copyPoint = currentPoint;
                    }
                }

                TemporalGeoPoint newPoint = TemporalGeoPoint(copyPoint);
                newPoint.timestamp = lastPoint->timestamp + (i+1)*newGap;
                returnTrajectory->addPosition(&newPoint);

                if (firstPointToCreate) {
                    returnTrajectory->addPosition(&newPoint);
                    returnTrajectory->addPosition(&newPoint);
                    firstPointToCreate = false;
                }
            } // adding new points
        } // if the gap between two point is > slotDuration

        if (indTGP < trajectory->trajectory->size()) {
            returnTrajectory->addPosition(currentPoint);
            if (firstPointToCreate) {
                returnTrajectory->addPosition(currentPoint);
                returnTrajectory->addPosition(currentPoint);
                firstPointToCreate = false;
            }
        }
        lastPoint = currentPoint;

    } // for all tgp in individual's trajectory

    returnTrajectory->addPosition(returnTrajectory->trajectory->back());
    returnTrajectory->addPosition(returnTrajectory->trajectory->back());
    return returnTrajectory;
}

/**
 * \brief 	Determines is the Trajectory has consistency
 * /// TODO check real usage
 */
void TrajectoryManager::order(Trajectory* trajectory) {
    //do I need ?
    vector<unsigned int> errorsPositions;
    TemporalGeoPoint* lastPoint = trajectory->trajectory->front();
    if (trajectory->trajectory->size() > 1) {
        for (unsigned int indTGP=1; indTGP<trajectory->trajectory->size(); indTGP++) {
            TemporalGeoPoint* currentPoint = trajectory->trajectory->at(indTGP);
            time_t gapTime = currentPoint->timestamp - lastPoint->timestamp;
            if (gapTime < 0) {
                errorsPositions.push_back(indTGP);
            }
        }
    }
    if (errorsPositions.size() <= 0) {

    } else if (errorsPositions.size() == 1) {
        cout << "1 error" << endl;
    } else if (errorsPositions.size() <= 2) {
        cout << " 2l errors" << endl;
    } else {
        cout << "ouch" << endl;
    }
}

/**
 * \brief 	Prints time gaps between consecutive TemporalGeoPoint of a trajectory
 * /// TODO check real usage
 */
void TrajectoryManager::infos(Trajectory* trajectory) {

    //TemporalGeoPoint* startPointTmp = trajectory->trajectory->front();
    //unsigned int lastIndex = trajectory->trajectory->size()-1;
    for (unsigned int indTGP=0; indTGP<trajectory->trajectory->size(); indTGP++) {
        TemporalGeoPoint* currentPoint = trajectory->trajectory->at(indTGP);

        // Distance avec les point précédents
        cout << "Dist: [";
        if (indTGP > 1) {
            TemporalGeoPoint* lastLastPoint = trajectory->trajectory->at(indTGP-2);
            double dist = geoMetrics::distanceTo(currentPoint, lastLastPoint);
            cout << dist << " ";
        } else {
            cout << "/ ";
        }
        if (indTGP > 0) {
            TemporalGeoPoint* lastPoint = trajectory->trajectory->at(indTGP-1);
            double dist = geoMetrics::distanceTo(currentPoint, lastPoint);
            cout << ", " << dist << " ";
        } else {
            cout << "/ ";
        }
        // Distance avec les point suivants
        cout << "; ";
        if (indTGP < trajectory->trajectory->size()-1) {
            TemporalGeoPoint* lastLastPoint = trajectory->trajectory->at(indTGP+1);
            double dist = geoMetrics::distanceTo(currentPoint, lastLastPoint);
            cout << dist << " ";
        } else {
            cout << "/ ";
        }
        if (indTGP < trajectory->trajectory->size()-2) {
            TemporalGeoPoint* lastPoint = trajectory->trajectory->at(indTGP+2);
            double dist = geoMetrics::distanceTo(currentPoint, lastPoint);
            cout << ", " << dist << " ";
        } else {
            cout << "/ ";
        }
        cout << "]" << endl;

        // Point 'centre' des +- 2 points

    }
}

/**
 * \brief 	Determines the stop and start periods of a trajectory and returns the different Trip within a trajectory
 *
 * \param 	trajectory          The Trajectory to analyze
 * \param   stopDuration        The minimal duration of a stop period (seconds)
 * \param   significantDistance The minimal distance to consider a displacement between two consecutive TemporalGeoPoint (meters)
 * \return 	The list of the different displacements observed within trajectory
 *
 * /!\ Important /!\ The return object and the Trajectory instances within it have to be deleted by the caller.
 * The stopDuration is expressed in seconds and the significantDistance in meters.
 */
std::unique_ptr<std::vector<unique_ptr<Trajectory>>> TrajectoryManager::extractTrips(Trajectory* trajectory, int stopDuration, double significantDistance, OGRSpatialReference* CSinput) {
    //cout << "start trip extract" << endl;
    unique_ptr<vector<unique_ptr<Trajectory>>> returnVector = make_unique<vector<unique_ptr<Trajectory>>>();

    TemporalGeoPoint* startPointTmp = trajectory->trajectory->front();
    TemporalGeoPoint* lastPoint = startPointTmp;
    //TemporalGeoPoint* lastStillPoint = startPointTmp;
    TemporalGeoPoint* currentPoint = startPointTmp;
    TemporalGeoPoint* PPA = startPointTmp;

    vector<unsigned int> indexesTGPTrip;
    int PPAindex = 0;
    time_t cumulatedTimeOnZone = 0;
    bool modeArret = true;
    bool alreadyAddedTrip = true;

    unsigned int lastIndex = trajectory->trajectory->size()-1;
    for (unsigned int indTGP=1; indTGP<lastIndex; indTGP++) {
        lastPoint = currentPoint;
        currentPoint = trajectory->trajectory->at(indTGP);
        //cout << "I1 ";
        bool currentHasMoved = geoMetrics::distanceTo(currentPoint, lastPoint, CSinput) >= significantDistance;
        cumulatedTimeOnZone = (currentPoint->timestamp - PPA->timestamp);
        //cout << (indTGP-1) << " -> " << indTGP << " (" << geoMetrics::distanceTo(currentPoint, lastPoint) << ")" << endl;
        //bool triggeredMoved = currentPoint->distanceTo(lastStillPoint) >= significantDistance;
        if (!currentHasMoved || indTGP >= lastIndex || (currentHasMoved && cumulatedTimeOnZone >= stopDuration)) {
            //cout << lastPoint->getX() << "," << lastPoint->getY() << " -> " << currentPoint->getX() << "," << currentPoint->getY() << " :still" << endl;
            //cout << (indTGP-1) << " -> " << indTGP << " :still";
                //cout << "I2 ";
            cumulatedTimeOnZone = (currentPoint->timestamp - PPA->timestamp);
            //cout << " cumulated time: " << str(cumulatedTimeOnZone, true) << endl;
            if (cumulatedTimeOnZone >= stopDuration || indTGP >= lastIndex) {
                //cout << "I3 ";
                if (indTGP >= lastIndex && currentHasMoved) {
                    if (indexesTGPTrip.back() != (indTGP-1)) indexesTGPTrip.push_back(indTGP-1);
                    indexesTGPTrip.push_back(indTGP);
                    PPAindex = indTGP;
                }
                //cout << "I4 ";
                if (!alreadyAddedTrip) {
                    modeArret = true;
                    alreadyAddedTrip = true;
                    unique_ptr<Trajectory> currentTrip = make_unique<Trajectory>();
                    unsigned int realSizeVectorTraj = indexesTGPTrip.size() - (indTGP-PPAindex-1);
                    for (unsigned int i=0; i<realSizeVectorTraj; i++) {
                        TemporalGeoPoint* pt = trajectory->trajectory->at(indexesTGPTrip[i]);
                        currentTrip->addPosition(pt);
                    }
                    //cout << " >>>>>>>>>>  created and added new trip to traj" << endl;
                    returnVector->push_back(std::move(currentTrip));
                    indexesTGPTrip.clear();
                }
            } else { //cumulatedTime < stop
                //cout << "E5 ";
                if (!modeArret) {
                    indexesTGPTrip.push_back(indTGP);
                }
            }
        } else { //has moved, or last point in trajectory
            //cout << lastPoint->getX() << "," << lastPoint->getY() << " -> " << currentPoint->getX() << "," << currentPoint->getY() << " :has moved" << endl;
            //cout << (indTGP-1) << " -> " << indTGP << " :has moved" << endl;
            //cout << "E6 ";
            if (modeArret) { //on était arreté avant ce hasMoved ?
                modeArret = false; //alors on est en mouvement
                alreadyAddedTrip = false;
                indexesTGPTrip.push_back(indTGP-1);
            }
            PPA = currentPoint;
            PPAindex = indTGP;
            indexesTGPTrip.push_back(indTGP);
        }
    }
    //cout << "end trip extract: " << returnVector->size() << endl;
    return returnVector;
}

/**
 * \brief 	Determines the stop and start periods of a trajectory and returns the different Trip within a trajectory
 *
 * \param 	trajectory          The Trajectory to analyze
 * \param   stopDuration        The minimal duration of a stop period (seconds)
 * \param   significantDistance The minimal distance to consider a displacement between two consecutive TemporalGeoPoint (meters)
 * \return 	The list of the different displacements observed within trajectory
 *
 * /!\ Important /!\ The return object and the Trajectory instances within it have to be deleted by the caller.
 * The stopDuration is expressed in seconds and the significantDistance in meters.
 */
unique_ptr<Trajectory> TrajectoryManager::cleanTrajectory(Trajectory* trajectory, double significantDistance, OGRSpatialReference* CSinput) {
    unique_ptr<Trajectory> returnTraj = unique_ptr<Trajectory>(new Trajectory(trajectory));
    this->cleanTrajectory(*(returnTraj.get()), significantDistance, CSinput);
    return returnTraj;
}

/**
 * \brief 	Determines the stop and start periods of a trajectory and returns the different Trip within a trajectory
 *
 * \param 	trajectory          The Trajectory to analyze
 * \param   stopDuration        The minimal duration of a stop period (seconds)
 * \param   significantDistance The minimal distance to consider a displacement between two consecutive TemporalGeoPoint (meters)
 * \return 	The list of the different displacements observed within trajectory
 *
 * /!\ Important /!\ The return object and the Trajectory instances within it have to be deleted by the caller.
 * The stopDuration is expressed in seconds and the significantDistance in meters.
 */
void TrajectoryManager::cleanTrajectory(Trajectory& trajectory, double significantDistance, OGRSpatialReference* CSinput) {
    if (trajectory.size() > 1) {
        TemporalGeoPoint* lastPoint = trajectory.trajectory->front();
        TemporalGeoPoint* currentPoint = lastPoint;
        vector<TemporalGeoPoint*>::iterator it = trajectory.trajectory->begin();
        while (it!=trajectory.trajectory->end()) {
            currentPoint = *it;
            if (geoMetrics::distanceTo(currentPoint, lastPoint, CSinput) < significantDistance) {
                trajectory.trajectory->erase(it);
            } else {
                lastPoint = currentPoint;
                it++;
            }
        }
    }
}



