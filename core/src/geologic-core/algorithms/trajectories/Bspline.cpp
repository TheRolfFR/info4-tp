/**
 * \file	Bspline.cpp
 * \class   Bspline
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Contains main methods to construct Bspline objects
 *
 * \details This class contains several methods used to construct Bspline objects, and to compute distances on Bspline objects.
 */

#include "geologic-core/algorithms/trajectories/Bspline.h"
#include "geologic-core/utils/customToolbox.h"
#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"
#include <memory>

using namespace std;
using namespace customToolbox;


/**
 * \brief 	Default constructor of class Bspline
 *
 * \param 	None
 * \return 	None
 *
 * The number of points to be projected between two reference points is set to 100
 */
Bspline::Bspline() {
    this->nbProjectedPoints = 100;
    this->dataRef = CoordinateSystemManager::getInstance()->getDataRef();
}

/**
 * \brief 	Default destructor of class Bspline
 *
 * \param 	None
 * \return 	None
 */
Bspline::~Bspline() {}

/**
 * \brief 	Constructor with parameters of class Bspline
 *
 * \param 	nbProjectedPoints   The number of points to be projected between two reference points
 * \return 	None
 */
Bspline::Bspline(int nbProjectedPoints) {
    this->nbProjectedPoints = nbProjectedPoints;
    this->dataRef = CoordinateSystemManager::getInstance()->getDataRef();
}

/**
 * \brief 	Default constructor of class GeologicEnvironment
 *
 * \param 	None
 * \return 	None
 */
void Bspline::setDataRef(OGRSpatialReference* dataRef) {
    this->dataRef = dataRef;
}

/**
 * \brief 	Default constructor of class GeologicEnvironment
 *
 * \param 	None
 * \return 	None
 */
OGRSpatialReference* Bspline::getDataRef() {
    return dataRef;
}

/**
 * \brief 	Computes the distance along an Euclidean approximation of the input Edge
 *
 * \param 	trajectory  The list of control points to analyze
 * \return 	The Euclidean distance between the control points of the trajectory
 */
//double Bspline::computeEuclideanDistance(Edge* edge) {
//    double EuclideanDistance = 0.0;
//    if (trajectory->trajectory->size() <= 1) return EuclideanDistance;
//
//    OGRPoint* lastPoint = trajectory->trajectory->at(0);
//    OGRPoint* currentPoint = lastPoint;
//    for (unsigned int i=1; i<trajectory->trajectory->size(); i++) {
//        currentPoint = trajectory->trajectory->at(i);
//        EuclideanDistance += geoMetrics::distanceTo(currentPoint, lastPoint);
//        lastPoint = currentPoint;
//    }
//
//    return EuclideanDistance;
//}

/**
 * \brief 	Computes the distance along an Euclidean approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \return 	The Euclidean distance between the control points of the trajectory
 */
 double Bspline::computeEuclideanDistance(Trajectory* trajectory) {
    double EuclideanDistance = 0.0;
    if (trajectory->trajectory->size() <= 1) return EuclideanDistance;

    OGRPoint* lastPoint = trajectory->trajectory->at(0);
    OGRPoint* currentPoint = lastPoint;
    for (unsigned int i=1; i<trajectory->trajectory->size(); i++) {
        currentPoint = trajectory->trajectory->at(i);
        EuclideanDistance += geoMetrics::distanceTo(currentPoint, lastPoint, this->dataRef);
        lastPoint = currentPoint;
    }

    return EuclideanDistance;
}

/**
 * \brief 	Computes the distance along a B-spline approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \param   splineOrder The order of the spline to use (default=3)
 * \return 	The distance between the projected points using a B-spline approximation
 */
 double Bspline::computeBsplineDistance(Trajectory* trajectory, int splineOrder) {
    double splineDistance = 0.0;
    if (trajectory->trajectory->size() <= 1) return splineDistance;

    std::unique_ptr<Trajectory> newTraj = this->computeBsplineTrajectory(trajectory, splineOrder);
    OGRPoint* lastPoint = newTraj->trajectory->at(0);
    OGRPoint* currentPoint = lastPoint;
    for (unsigned int i=1; i<newTraj->trajectory->size(); i++) {
        currentPoint = newTraj->trajectory->at(i);
        splineDistance += geoMetrics::distanceTo(currentPoint, lastPoint, this->dataRef);
        lastPoint = currentPoint;
    }
    return splineDistance;
}

/**
 * \brief 	Computes the distance along a gravity-like model approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \param   glmFactor   The factor used to detected the next control point (default=0.75)
 * \return 	The distance between the projected points using a gravity-like model approximation
 */
 double Bspline::computeGravityLikeModelDistance(Trajectory* trajectory, double glmFactor) {
    double glmDistance = 0.0;
    if (trajectory->trajectory->size() <= 1) return glmDistance;

    std::unique_ptr<Trajectory> newTraj = this->computeGravityLikeModelTrajectory(trajectory, glmFactor);
    OGRPoint* lastPoint = newTraj->trajectory->at(0);
    OGRPoint* currentPoint = lastPoint;
    for (unsigned int i=1; i<newTraj->trajectory->size(); i++) {
        currentPoint = newTraj->trajectory->at(i);
        glmDistance += geoMetrics::distanceTo(currentPoint, lastPoint, this->dataRef);
        lastPoint = currentPoint;
    }
    return glmDistance;
}

/**
 * \brief 	Computes the distance along a smoothed B-spline approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \param   sbFactor    The factor used to start the new B-spline approximation (default=0.5)
 * \return 	The distance between the projected points using a smooth B-spline approximation
 */
 double Bspline::computeSmoothedBsplineDistance(Trajectory* trajectory, double sbFactor) {
    double sbDistance = 0.0;
    if (trajectory->trajectory->size() <= 1) return sbDistance;

    std::unique_ptr<Trajectory> newTraj = this->computeSmoothedBsplineTrajectory(trajectory, sbFactor);
    OGRPoint* lastPoint = newTraj->trajectory->at(0);
    OGRPoint* currentPoint = lastPoint;
    for (unsigned int i=1; i<newTraj->trajectory->size(); i++) {
        currentPoint = newTraj->trajectory->at(i);
        sbDistance += geoMetrics::distanceTo(currentPoint, lastPoint, this->dataRef);
        lastPoint = currentPoint;
    }
    return sbDistance;
}

/**
 * \brief 	Computes the distance along a fixed B-spline-rounded model approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \param   fbrFactor   The factor used to start the next B-spline (default=0.6)
 * \return 	The distance between the projected points using a fixed B-spline-rounded model approximation
 */
 double Bspline::computeFixedBsplineRoundedModelDistance(Trajectory* trajectory, double fbrFactor) {
    double fbrDistance = 0.0;
    if (trajectory->trajectory->size() <= 1) return fbrDistance;

    std::unique_ptr<Trajectory> newTraj = this->computeFixedBsplineRoundedModelTrajectory(trajectory, fbrFactor);
    TemporalGeoPoint* lastPoint = newTraj->trajectory->at(0);
    TemporalGeoPoint* currentPoint = lastPoint;
    for (unsigned int i=1; i<newTraj->trajectory->size(); i++) {
        currentPoint = newTraj->trajectory->at(i);
        fbrDistance += geoMetrics::distanceTo(currentPoint, lastPoint, this->dataRef);
        lastPoint = currentPoint;
    }
    return fbrDistance;
}

/**
 * \brief 	Computes the distance along an automatic B-spline-rounded model approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \param   zones       The list of zones used to start the next B-spline
 * \return 	The distance between the projected points using an automatic B-spline-rounded model approximation
 *
 * We assume that the control points are located within a zone of the input map.
 */
 double Bspline::computeAutomaticBsplineRoundedModelDistance(Trajectory* trajectory, std::unordered_map<std::string, GeoZone*>* zones) {
    double abrDistance = 0.0;
    if (trajectory->trajectory->size() <= 1) return abrDistance;
    if (zones == NULL) return abrDistance;

    std::unique_ptr<Trajectory> newTraj = this->computeAutomaticBsplineRoundedModelTrajectory(trajectory, zones);
    OGRPoint* lastPoint = newTraj->trajectory->at(0);
    OGRPoint* currentPoint = lastPoint;

    for (unsigned int i=1; i<newTraj->trajectory->size(); i++) {
        currentPoint = newTraj->trajectory->at(i);
        abrDistance += geoMetrics::distanceTo(currentPoint, lastPoint, this->dataRef);
        lastPoint = currentPoint;
    }
    return abrDistance;
}

/**
 * \brief 	Generates a new Trajectory with an Euclidean approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \return 	The address of a new Trajectory generated based on an Euclidean approximation
 *
 * /!\ Important /!\ The returned Trajectory will have to be deleted by the caller in order to avoid memory leaks
 */
std::unique_ptr<Trajectory> Bspline::computeEuclideanTrajectory(Trajectory* trajectory) {
    std::unique_ptr<Trajectory> outputTraj = std::make_unique<Trajectory>();
    if (trajectory->trajectory->size() <= 1) return outputTraj;

    TemporalGeoPoint* lastPoint = trajectory->trajectory->at(0);
    TemporalGeoPoint* currentPoint = lastPoint;
    outputTraj->addPosition(lastPoint);

    for (unsigned int indPoint=1; indPoint<trajectory->trajectory->size(); indPoint++) {
        currentPoint = trajectory->trajectory->at(indPoint);
        double incX = (currentPoint->getX() - lastPoint->getX()) / this->nbProjectedPoints;
        double incY = (currentPoint->getY() - lastPoint->getY()) / this->nbProjectedPoints;
        double incT = (currentPoint->timestamp - lastPoint->timestamp) / this->nbProjectedPoints;
        for (int i=0; i<this->nbProjectedPoints; i++) {
            //pair<string, string> tag = pair<string, string>("type", "intermediate Euclidean position");
            TemporalGeoPoint newPoint = TemporalGeoPoint(lastPoint->getX()+i*incX, lastPoint->getY()+i*incY, lastPoint->getZ(), lastPoint->timestamp+incT);
            outputTraj->addPosition(&newPoint);
        }
        lastPoint = currentPoint;
    }

    return outputTraj;
}

/**
 * \brief 	Generates a new Trajectory with a B-spline approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \param   splineOrder The order of the spline (default=3)
 * \return 	The address of a new Trajectory generated based on a B-spline approximation
 *
 * /!\ Important /!\ The returned Trajectory will have to be deleted by the caller in order to avoid memory leaks
 */
std::unique_ptr<Trajectory> Bspline::computeBsplineTrajectory(Trajectory* trajectory, int splineOrder) {

    trajectory->addPosition(trajectory->trajectory->back()); // To correctly end the Bspline
    int numberOfControlPoints = trajectory->trajectory->size();
    splineOrder = min(numberOfControlPoints, splineOrder);
    unsigned int numberOfProjectedPoints = (numberOfControlPoints)*this->nbProjectedPoints;

    std::unique_ptr<Trajectory> outputTraj = std::make_unique<Trajectory>();
    if (numberOfControlPoints <= 1) return outputTraj;
    //pair<string, string> tag = pair<string, string>("type", "intermediate B-spline position");

    // we first fill up the outputTraj
    TemporalGeoPoint* ps = trajectory->trajectory->front();
    //TemporalGeoPoint* pl = trajectory->trajectory->back();

    for (unsigned int i=0; i<numberOfProjectedPoints; i++) {
        double currentTime = ps->timestamp;// + i*incT;
        TemporalGeoPoint tmp = TemporalGeoPoint(0.0, 0.0, 0.0, currentTime);
        outputTraj->addPosition(&tmp);
    }

    vector<map<string, double> > tempVectForTimestamp;
    for (unsigned int i=0; i<trajectory->trajectory->size()-1; i++) {
        tempVectForTimestamp.push_back(map<string, double> {{"minDist", -1.0}, {"index", -1}, {"watchdog", 0}});
    }

    if (numberOfControlPoints >= splineOrder) {
        vector<double> knots;
        unsigned int nbKnots = (numberOfControlPoints-splineOrder+1);
        for (int i=0; i<splineOrder; i++) knots.push_back(0.0);
        for (unsigned int s=1; s<=nbKnots; s++) knots.push_back(((double) s));
        for (int i=0; i<splineOrder; i++) knots.push_back(nbKnots);


        //int currentControlPoint = 1;
        //double currentDistance = -1;

        for (unsigned int i=0; i<numberOfProjectedPoints; i++) {
            double projectedKnotU = ((double) i)/numberOfProjectedPoints*nbKnots;
            double xU = 0.0;
            double yU = 0.0;

            for(int indPointTraj=0; indPointTraj<numberOfControlPoints; indPointTraj++) {
                double factor = this->CoxDeBoorRecursion(&knots, indPointTraj, splineOrder, projectedKnotU);
                xU += factor * trajectory->trajectory->at(indPointTraj)->getX();
                yU += factor * trajectory->trajectory->at(indPointTraj)->getY();
            }
            outputTraj->trajectory->at(i)->setX(xU);
            outputTraj->trajectory->at(i)->setY(yU);

            for (unsigned int ii=1; ii<trajectory->trajectory->size(); ii++) {
                if (tempVectForTimestamp[(ii-1)]["watchdog"] < 10) {
                    double distTmp = geoMetrics::distanceTo(outputTraj->trajectory->at(i), trajectory->trajectory->at(ii), this->dataRef);
                    if (tempVectForTimestamp[(ii-1)]["minDist"] == -1 || distTmp <= tempVectForTimestamp[(ii-1)]["minDist"]) {
                        tempVectForTimestamp[(ii-1)]["minDist"] = distTmp;
                        tempVectForTimestamp[(ii-1)]["index"] = i;
                    } else {
                        tempVectForTimestamp[(ii-1)]["watchdog"]++;
                    }
                }
            }
        }
    }

    this->redresseTimestamp(&tempVectForTimestamp, trajectory, outputTraj.get());
    trajectory->trajectory->pop_back(); // pop back ?
    return outputTraj;
}

/**
 * \brief 	Generates a new Trajectory with a gravity-like model approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \param   glmFactor   The factor used to detected the next control point (default=0.75)
 * \return 	The address of a new Trajectory generated based on a gravity-like model approximation
 *
 * /!\ Important /!\ The returned Trajectory will have to be deleted by the caller in order to avoid memory leaks
 */
std::unique_ptr<Trajectory> Bspline::computeGravityLikeModelTrajectory(Trajectory* trajectory, double glmFactor) {
    unsigned int lenTraj = trajectory->trajectory->size();
    int maxObjectives = 2;

    std::unique_ptr<Trajectory> outputTraj = std::make_unique<Trajectory>();
    if (lenTraj <= 1) return outputTraj;
    pair<string, string> tag = pair<string, string>("type", "intermediate gravity-like model position");

    // we first fill up the outputTraj
    for (unsigned int i=0; i<this->nbProjectedPoints*(trajectory->trajectory->size()-1); i++) {
        TemporalGeoPoint tmp = TemporalGeoPoint(0.0, 0.0, 0.0, trajectory->trajectory->at(0)->timestamp);
        outputTraj->addPosition(&tmp);
    }

    vector<map<string, double> > tempVectForTimestamp;
    for (unsigned int i=0; i<trajectory->trajectory->size()-1; i++) {
        tempVectForTimestamp.push_back(map<string, double> {{"minDist", -1.0}, {"index", -1}, {"watchdog", 0}});
    }

    deque<TemporalGeoPoint*> objectives;
    objectives.push_back(trajectory->trajectory->at(1));
    TemporalGeoPoint* lastPosition = trajectory->trajectory->at(0);

    for (unsigned int i=0; i<trajectory->trajectory->size()-1; i++) {

        for (int indInterval=0; indInterval<this->nbProjectedPoints; indInterval++) {
            TemporalGeoPoint* p1 = objectives[0];
            double factor = 1.0;
            double factor2 = 1.0;
            double incX = (p1->getX()-lastPosition->getX()) / (this->nbProjectedPoints-indInterval);
            double incY = (p1->getY()-lastPosition->getY()) / (this->nbProjectedPoints-indInterval);
            double incX2 = 0.0;
            double incY2 = 0.0;

            if (indInterval > this->nbProjectedPoints*glmFactor) {
                if (i < trajectory->trajectory->size()-maxObjectives) {
                    if (objectives.size() <= 1) objectives.push_back(trajectory->trajectory->at(i+2));
                    TemporalGeoPoint* p2 = objectives[1];

                    factor2 = (indInterval-(this->nbProjectedPoints*glmFactor))/(3*this->nbProjectedPoints*(1-glmFactor));
                    factor = (1-factor2);
                    incX2 = (p2->getX()-lastPosition->getX()) / (this->nbProjectedPoints-indInterval);
                    incY2 = (p2->getY()-lastPosition->getY()) / (this->nbProjectedPoints-indInterval);
                }
            }

            int posOutput = i*this->nbProjectedPoints+indInterval;
            outputTraj->trajectory->at(posOutput)->setX(lastPosition->getX()+factor*incX+factor2*incX2);
            outputTraj->trajectory->at(posOutput)->setY(lastPosition->getY()+factor*incY+factor2*incY2);
            lastPosition = outputTraj->trajectory->at(posOutput);

            for (unsigned int ii=1; ii<trajectory->trajectory->size(); ii++) {
                if (tempVectForTimestamp[(ii-1)]["watchdog"] < 10) {
                    double distTmp = geoMetrics::distanceTo(outputTraj->trajectory->at(posOutput), trajectory->trajectory->at(ii), this->dataRef);
                    if (tempVectForTimestamp[(ii-1)]["minDist"] == -1 || distTmp <= tempVectForTimestamp[(ii-1)]["minDist"]) {
                        tempVectForTimestamp[(ii-1)]["minDist"] = distTmp;
                        tempVectForTimestamp[(ii-1)]["index"] = posOutput;
                    } else {
                        tempVectForTimestamp[(ii-1)]["watchdog"]++;
                    }
                }
            }

        }
        objectives.pop_front();
    }

    this->redresseTimestamp(&tempVectForTimestamp, trajectory, outputTraj.get());
    objectives.clear();
    return outputTraj;
}

/**
 * \brief 	Generates a new Trajectory with a fixed B-spline-rounded model approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \param   fbrFactor   The factor used to detected the next control point (default=0.6)
 * \return 	The address of a new Trajectory generated based on a fixed B-spline-rounded model approximation
 *
 * /!\ Important /!\ The returned Trajectory will have to be deleted by the caller in order to avoid memory leaks
 */
std::unique_ptr<Trajectory> Bspline::computeFixedBsplineRoundedModelTrajectory(Trajectory* trajectory, double fbrFactor) {
    unsigned int lenTraj = trajectory->trajectory->size();
    double coeffEntering = (1-fbrFactor);

    unsigned int echant = 2*this->nbProjectedPoints*coeffEntering; // échantillonage pour le moment (100)

    std::unique_ptr<Trajectory> outputTraj = std::make_unique<Trajectory>();
    if (lenTraj <= 1) return outputTraj;
    pair<string, string> tag = pair<string, string>("type", "intermediate fixed B-spline-rounded model position");

    // we first fill up the outputTraj
    for (unsigned int i=0; i<this->nbProjectedPoints*(trajectory->trajectory->size()-1); i++) {
        TemporalGeoPoint tmp = TemporalGeoPoint(0.0, 0.0, 0.0, trajectory->trajectory->at(0)->timestamp);
        outputTraj->addPosition(&tmp);
    }

    vector<map<string, double> > tempVectForTimestamp;
    for (unsigned int i=0; i<trajectory->trajectory->size()-1; i++) {
        tempVectForTimestamp.push_back(map<string, double> {{"minDist", -1.0}, {"index", -1}, {"watchdog", 0}});
    }

    deque<TemporalGeoPoint*> objectives;
    objectives.push_back(trajectory->trajectory->at(1));
    TemporalGeoPoint* lastPosition = trajectory->trajectory->at(0);
    TemporalGeoPoint* p0 = NULL;
    TemporalGeoPoint* p1s = NULL;

    for (unsigned int i=0; i<trajectory->trajectory->size()-1; i++) {
        int indInterval = 0;
        //if (i > 0) indInterval = this->nbProjectedPoints*coeffEntering;

        for (; indInterval<this->nbProjectedPoints; indInterval++) {
            TemporalGeoPoint* p1 = objectives[0];
            double incX = (p1->getX()-lastPosition->getX()) / (this->nbProjectedPoints-indInterval);
            double incY = (p1->getY()-lastPosition->getY()) / (this->nbProjectedPoints-indInterval);

            int posOutput = i*this->nbProjectedPoints+indInterval;

            if (i > 0 && indInterval < this->nbProjectedPoints*coeffEntering) {
                //*/
                TemporalGeoPoint* p2Far = objectives[0];
                double p2x = p1s->getX() + (p2Far->getX()-p1s->getX())*coeffEntering;
                double p2y = p1s->getY() + (p2Far->getY()-p1s->getY())*coeffEntering;
                double inc01X = (p1s->getX()-p0->getX())/echant;
                double inc01Y = (p1s->getY()-p0->getY())/echant;
                double inc12X = (p2x-p1s->getX())/echant;
                double inc12Y = (p2y-p1s->getY())/echant;

                int indEchant = indInterval + (this->nbProjectedPoints*coeffEntering);
                double posX = (p0->getX()+indEchant*inc01X) + indEchant*(((p1s->getX()+indEchant*inc12X) - (p0->getX()+indEchant*inc01X))/echant);
                double posY = (p0->getY()+indEchant*inc01Y) + indEchant*(((p1s->getY()+indEchant*inc12Y) - (p0->getY()+indEchant*inc01Y))/echant);

                outputTraj->trajectory->at(posOutput)->setX(posX);
                outputTraj->trajectory->at(posOutput)->setY(posY);
                //*/

            } else if (i < trajectory->trajectory->size()-2 && indInterval >= this->nbProjectedPoints*fbrFactor) {
                if (i < trajectory->trajectory->size()-2) {
                    if (objectives.size() <= 1) {
                        objectives.push_back(trajectory->trajectory->at(i+2));
                        p0 = lastPosition;
                    }

                    p1s = p1;
                    TemporalGeoPoint* p2Far = objectives[1];
                    //on va commencer a former une bspline
                    double p2x = p1->getX() + (p2Far->getX()-p1->getX())*coeffEntering;
                    double p2y = p1->getY() + (p2Far->getY()-p1->getY())*coeffEntering;
                    double inc01X = (p1->getX()-p0->getX())/echant;
                    double inc01Y = (p1->getY()-p0->getY())/echant;
                    double inc12X = (p2x-p1->getX())/echant;
                    double inc12Y = (p2y-p1->getY())/echant;

                    int indEchant = indInterval - (this->nbProjectedPoints*fbrFactor);
                    double posX = (p0->getX()+indEchant*inc01X) + indEchant*(((p1->getX()+indEchant*inc12X) - (p0->getX()+indEchant*inc01X))/echant);
                    double posY = (p0->getY()+indEchant*inc01Y) + indEchant*(((p1->getY()+indEchant*inc12Y) - (p0->getY()+indEchant*inc01Y))/echant);

                    outputTraj->trajectory->at(posOutput)->setX(posX);
                    outputTraj->trajectory->at(posOutput)->setY(posY);

                    for (unsigned int ii=1; ii<trajectory->trajectory->size(); ii++) {
                        if (tempVectForTimestamp[(ii-1)]["watchdog"] < 10) {
                            double distTmp = geoMetrics::distanceTo(outputTraj->trajectory->at(posOutput), trajectory->trajectory->at(ii), this->dataRef);
                            if (tempVectForTimestamp[(ii-1)]["minDist"] == -1 || distTmp <= tempVectForTimestamp[(ii-1)]["minDist"]) {
                                tempVectForTimestamp[(ii-1)]["minDist"] = distTmp;
                                tempVectForTimestamp[(ii-1)]["index"] = posOutput;
                            } else {
                                tempVectForTimestamp[(ii-1)]["watchdog"]++;
                            }
                        }
                    }
                }
            } else {
                outputTraj->trajectory->at(posOutput)->setX(lastPosition->getX()+incX);
                outputTraj->trajectory->at(posOutput)->setY(lastPosition->getY()+incY);
                for (unsigned int ii=1; ii<trajectory->trajectory->size(); ii++) {
                    if (tempVectForTimestamp[(ii-1)]["watchdog"] < 10) {
                        double distTmp = geoMetrics::distanceTo(outputTraj->trajectory->at(posOutput), trajectory->trajectory->at(ii), this->dataRef);
                        if (tempVectForTimestamp[(ii-1)]["minDist"] == -1 || distTmp < tempVectForTimestamp[(ii-1)]["minDist"]) {
                            tempVectForTimestamp[(ii-1)]["minDist"] = distTmp;
                            tempVectForTimestamp[(ii-1)]["index"] = posOutput;
                        } else {
                            tempVectForTimestamp[(ii-1)]["watchdog"]++;
                        }
                    }
                }
            }

            lastPosition = outputTraj->trajectory->at(posOutput);
        }
        objectives.pop_front();
    }

    this->redresseTimestamp(&tempVectForTimestamp, trajectory, outputTraj.get());
    return outputTraj;
}

/**
 * \brief 	Generates a new Trajectory with an automatic B-spline-rounded model approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \param   zones       The list of zones used to start the next B-spline
 * \return 	The address of a new Trajectory generated based on an automatic B-spline-rounded model approximation
 *
 * /!\ Important /!\ The returned Trajectory will have to be deleted by the caller in order to avoid memory leaks
 */
std::unique_ptr<Trajectory> Bspline::computeAutomaticBsplineRoundedModelTrajectory(Trajectory* trajectory, std::unordered_map<std::string, GeoZone*>* zones) {
    unsigned int lenTraj = trajectory->trajectory->size();

    //--------------------------------------//
    //                   *                  //
    //                  * *                 //
    //--------------------------------------//

    std::unique_ptr<Trajectory> outputTraj = std::make_unique<Trajectory>();
    if (lenTraj <= 1) return outputTraj;
    pair<string, string> tag = pair<string, string>("type", "intermediate Automatic B-spline-rounded model position");

    // we first fill up the outputTraj
    for (unsigned int i=0; i<this->nbProjectedPoints*(trajectory->trajectory->size()-1); i++) {
        TemporalGeoPoint tmp = TemporalGeoPoint(0.0, 0.0, 0.0, trajectory->trajectory->at(0)->timestamp);
        outputTraj->addPosition(&tmp);
    }

    vector<map<string, double> > tempVectForTimestamp;
    for (unsigned int i=0; i<trajectory->trajectory->size()-1; i++) {
        tempVectForTimestamp.push_back(map<string, double> {{"minDist", -1.0}, {"index", -1}, {"watchdog", 0}});
    }

    deque<TemporalGeoPoint*> objectives;
    objectives.push_back(trajectory->trajectory->at(1));
    TemporalGeoPoint* lastPosition = trajectory->trajectory->at(0);
    TemporalGeoPoint* p0 = NULL;
    TemporalGeoPoint* p1s = NULL;
    double coeffp1p2Entering = 0;
    double echantp1p2 = 0;
    //string outFileStr = "./datas/log.csv";
    //std::ofstream ofs;
    //ofs.open(outFileStr);
    //string outputString = "";

    //ofs << "\n__INIT__  " << str(lastPosition->timestamp) << " - " << str(trajectory->trajectory->back()->timestamp) << " (" << trajectory->trajectory->size() << " pts)" << endl;
    for (unsigned int i=0; i<trajectory->trajectory->size()-1; i++) {
        int indInterval = 0;

        //--------------------------------------//
        //                   *                  //
        //                  * *                 //
        //--------------------------------------//

        //on va calculer la distance entre i et i+1
        double distTop1 = geoMetrics::distanceTo(trajectory->trajectory->at(i), trajectory->trajectory->at(i+1), this->dataRef);
        //on va chercher a trouver les positions qui coupent le segment i, i+1
        //ofs << "\nindex: " << i << " (" << str(trajectory->trajectory->at(i)->timestamp) << " -> " << str(trajectory->trajectory->at(i+1)->timestamp) <<")  distance i, i+1: " << distTop1 << endl;
        TemporalGeoPoint* ptTemp = trajectory->trajectory->at(i+1);
        GeoZone* zoneDest = zones->at(ptTemp->listTags["radioCell"]); //type ??
        GeologicGeometricalObject objTmp;

        double minDistTop1 = -1;
        for (unsigned int seg=0; seg<zoneDest->getNumPoints(); seg++) {
            shared_ptr<OGRPoint> pa = zoneDest->getPoint(seg);
            int seg1 = seg+1;
            if (seg >= zoneDest->getNumPoints()-1) seg1 = 0;
            shared_ptr<OGRPoint> pb = zoneDest->getPoint(seg1);

            /// TODO check real usage of this code
            /// La fonction areSegmentsCrossing n'existe plus, le bout de code n'a plus lieu d'être
//            if (objTmp.areSegmentsCrossing(pa.get(), pb.get(), trajectory->trajectory->at(i), trajectory->trajectory->at(i+1))) {
//                OGRPoint* inter = objTmp.computeIntersection(pa.get(), pb.get(), trajectory->trajectory->at(i), trajectory->trajectory->at(i+1)); //to delete
//                double distTmp = distTop1;
//                if (inter != NULL) distTmp = geoMetrics::distanceTo(trajectory->trajectory->at(i), inter);
//                if (minDistTop1 == -1 || distTmp <= minDistTop1) {
//                    minDistTop1 = distTmp;
//                }
//                if (inter != NULL) delete(inter);
//                inter = NULL;
//            }
        }

        //cout << "    Min dist(" << minDistTop1 << ") ";
        //une fois que l'on a la distance minimale, on peut calculer son coeff
        double roundSmoothFactor = 0.01;
        if (distTop1 > 0) roundSmoothFactor = minDistTop1/distTop1;
        if (roundSmoothFactor <= 0.01) roundSmoothFactor = 0.01;
        if (roundSmoothFactor >= 0.99) roundSmoothFactor = 0.99;
        int escapeInd = this->nbProjectedPoints*roundSmoothFactor;
        double coeffp0p1Leaving = (1-roundSmoothFactor);
        unsigned int echantp0p1 = 2*this->nbProjectedPoints*coeffp0p1Leaving; // échantillonage pour le moment (100)

        //ofs << "   " << "distTop1: " << minDistTop1 << " roundsmooth: " << roundSmoothFactor << " coeffleaving: " << coeffp0p1Leaving << "  " << objectives.size() << endl;

        //--------------------------------------//
        //                   *                  //
        //                  * *                 //
        //--------------------------------------//

        for (; indInterval<this->nbProjectedPoints; indInterval++) {
            TemporalGeoPoint* p1 = objectives[0];


            double incX = (p1->getX()-lastPosition->getX()) / (this->nbProjectedPoints-indInterval);
            double incY = (p1->getY()-lastPosition->getY()) / (this->nbProjectedPoints-indInterval);
            int enteringId = this->nbProjectedPoints*coeffp1p2Entering;
            //if (incT < 0) incT = 1;
            //ofs << "Interval: " << indInterval << "(" << (this->nbProjectedPoints-indInterval) << ")  incT: " << incT << endl;
            //ofs << "  " << str(p1->timestamp) << " -> " << str(lastPosition->timestamp) << "  = " << (p1->timestamp-lastPosition->timestamp) << endl;
            //ofs << "escapeInd: " << escapeInd << "  entering: " << (enteringId) << endl;
            int posOutput = i*this->nbProjectedPoints+indInterval;

            if (i > 0 && indInterval < enteringId) {
                //ofs << " (" << indInterval << ", if1) " << endl;
                //*/
                TemporalGeoPoint* p2Far = objectives[0];
                double p2x = p1s->getX() + (p2Far->getX()-p1s->getX())*coeffp1p2Entering;
                double p2y = p1s->getY() + (p2Far->getY()-p1s->getY())*coeffp1p2Entering;
                //double p2t = p1s->timestamp + (p2Far->timestamp-p1s->timestamp)*coeffp1p2Entering;
                double inc01X = (p1s->getX()-p0->getX())/echantp1p2;
                double inc01Y = (p1s->getY()-p0->getY())/echantp1p2;
                double inc12X = (p2x-p1s->getX())/echantp1p2;
                double inc12Y = (p2y-p1s->getY())/echantp1p2;
                //double inc12T = (p2t-p1s->timestamp)/echantp1p2;
                int indEchant = indInterval + (enteringId);

                double posX = (p0->getX()+indEchant*inc01X) + indEchant*(((p1s->getX()+indEchant*inc12X) - (p0->getX()+indEchant*inc01X))/echantp1p2);
                double posY = (p0->getY()+indEchant*inc01Y) + indEchant*(((p1s->getY()+indEchant*inc12Y) - (p0->getY()+indEchant*inc01Y))/echantp1p2);
                //double posT = p1s->timestamp + indEchant*inc12T;
                outputTraj->trajectory->at(posOutput)->setX(posX);
                outputTraj->trajectory->at(posOutput)->setY(posY);
                //outputTraj->trajectory->at(posOutput)->timestamp = posT;
                //*/

            } else if (i < trajectory->trajectory->size()-2 && indInterval >= escapeInd) {
                //ofs << " (" << indInterval << ", Elif) " << endl;
                if (i < trajectory->trajectory->size()-2) {
                    //ofs << " (" << indInterval << ", if2) " << endl;
                    if (objectives.size() <= 1) {
                        //ofs << "  ------- newPO (" << echantp0p1 << ")" << endl;
                        objectives.push_back(trajectory->trajectory->at(i+2));
                        p0 = lastPosition;
                    }

                    p1s = p1;
                    TemporalGeoPoint* p2Far = objectives[1];

                    //on va commencer a former une bspline
                    double p2x = p1->getX() + (p2Far->getX()-p1->getX())*coeffp0p1Leaving;
                    double p2y = p1->getY() + (p2Far->getY()-p1->getY())*coeffp0p1Leaving;
                    double inc01X = (p1->getX()-p0->getX())/echantp0p1;
                    double inc01Y = (p1->getY()-p0->getY())/echantp0p1;
                    double inc12X = (p2x-p1->getX())/echantp0p1;
                    double inc12Y = (p2y-p1->getY())/echantp0p1;
                    //double inc01T = (p1->timestamp-p0->timestamp)/echantp0p1;
                    //cout << str(p1->timestamp) << " <- " << str(p0->timestamp) << "  incO1T: " << inc01T << endl;
                    int indEchant = indInterval - (escapeInd);
                    double posX = (p0->getX()+indEchant*inc01X) + indEchant*(((p1->getX()+indEchant*inc12X) - (p0->getX()+indEchant*inc01X))/echantp0p1);
                    double posY = (p0->getY()+indEchant*inc01Y) + indEchant*(((p1->getY()+indEchant*inc12Y) - (p0->getY()+indEchant*inc01Y))/echantp0p1);
                    //double posT = p0->timestamp + indEchant*inc01T;

                    outputTraj->trajectory->at(posOutput)->setX(posX);
                    outputTraj->trajectory->at(posOutput)->setY(posY);
                    for (unsigned int ii=1; ii<trajectory->trajectory->size(); ii++) {
                            if (tempVectForTimestamp[(ii-1)]["watchdog"] < 10) {
                                double distTmp = geoMetrics::distanceTo(outputTraj->trajectory->at(posOutput), trajectory->trajectory->at(ii), this->dataRef);
                                if (tempVectForTimestamp[(ii-1)]["minDist"] == -1 || distTmp <= tempVectForTimestamp[(ii-1)]["minDist"]) {
                                    tempVectForTimestamp[(ii-1)]["minDist"] = distTmp;
                                    tempVectForTimestamp[(ii-1)]["index"] = posOutput;
                                } else {
                                    tempVectForTimestamp[(ii-1)]["watchdog"]++;
                                }
                            }
                        }

                }
            } else {

                outputTraj->trajectory->at(posOutput)->setX(lastPosition->getX()+incX);
                outputTraj->trajectory->at(posOutput)->setY(lastPosition->getY()+incY);
                for (unsigned int ii=1; ii<trajectory->trajectory->size(); ii++) {
                    if (tempVectForTimestamp[(ii-1)]["watchdog"] < 10) {
                        double distTmp = geoMetrics::distanceTo(outputTraj->trajectory->at(posOutput), trajectory->trajectory->at(ii), this->dataRef);
                        if (tempVectForTimestamp[(ii-1)]["minDist"] == -1 || distTmp <= tempVectForTimestamp[(ii-1)]["minDist"]) {
                            tempVectForTimestamp[(ii-1)]["minDist"] = distTmp;
                            tempVectForTimestamp[(ii-1)]["index"] = posOutput;
                        } else {
                            tempVectForTimestamp[(ii-1)]["watchdog"]++;
                        }
                    }
                }
            }
            lastPosition = outputTraj->trajectory->at(posOutput);

        }

        objectives.pop_front();
        coeffp1p2Entering = coeffp0p1Leaving; //pour le prochain segment
        echantp1p2 = 2*this->nbProjectedPoints*coeffp1p2Entering; //pour le prochain segment

    }
    //ofs << "### End ###\n" << endl;
    //ofs.close();
    this->redresseTimestamp(&tempVectForTimestamp, trajectory, outputTraj.get());
    return outputTraj;
}

/**
 * \brief 	Generates a new Trajectory with a smoothed B-spline approximation of the input Trajectory
 *
 * \param 	trajectory  The list of control points to analyze
 * \param   sbFactor    The factor used to detected the next control point (default=0.5)
 * \return 	The address of a new Trajectory generated based on a smoothed B-spline approximation
 *
 * /!\ Important /!\ The returned Trajectory will have to be deleted by the caller in order to avoid memory leaks
 */
std::unique_ptr<Trajectory> Bspline::computeSmoothedBsplineTrajectory(Trajectory* trajectory, double sbFactor) {
    unsigned int lenTraj = trajectory->trajectory->size();
    unsigned int echant = this->nbProjectedPoints/sbFactor; // échantillonage pour le moment (100)

    std::unique_ptr<Trajectory> outputTraj = std::make_unique<Trajectory>();
    if (lenTraj <= 1) return outputTraj;
    pair<string, string> tag = pair<string, string>("type", "intermediate smoothed B-spline position");

    // we first fill up the outputTraj
    for (unsigned int i=0; i<this->nbProjectedPoints*(trajectory->trajectory->size()); i++) {
        TemporalGeoPoint tmp = TemporalGeoPoint(0.0, 0.0, 0.0, trajectory->trajectory->at(0)->timestamp);
        outputTraj->addPosition(&tmp);
    }

    vector<map<string, double> > tempVectForTimestamp;
    for (unsigned int i=0; i<trajectory->trajectory->size()-1; i++) {
        tempVectForTimestamp.push_back(map<string, double> {{"minDist", -1.0}, {"index", -1}, {"watchdog", 0}});
    }

    deque<TemporalGeoPoint*> objectives;
    objectives.push_back(trajectory->trajectory->at(1));
    TemporalGeoPoint* p0 = trajectory->trajectory->at(0);
    int posOutput = 0;
    outputTraj->trajectory->at(posOutput)->setX(p0->getX());
    outputTraj->trajectory->at(posOutput)->setY(p0->getY());
    outputTraj->trajectory->at(posOutput)->timestamp = p0->timestamp;

    for (unsigned int i=0; i<trajectory->trajectory->size(); i++) {
        TemporalGeoPoint* p1 = objectives[0];
        int incTmp = 2;
        if (i >= trajectory->trajectory->size()-2) incTmp = 1;
        if (i >= trajectory->trajectory->size()-1) {
            incTmp = 0;
            echant = this->nbProjectedPoints;
        }
        objectives.push_back(trajectory->trajectory->at(i+incTmp));
        TemporalGeoPoint* p2 = objectives[1];

        double inc01X = (p1->getX()-p0->getX())/echant;
        double inc01Y = (p1->getY()-p0->getY())/echant;
        double inc12X = (p2->getX()-p1->getX())/echant;
        double inc12Y = (p2->getY()-p1->getY())/echant;

        for (int indEchant=0; indEchant<this->nbProjectedPoints; indEchant++) {
            double posX = (p0->getX()+indEchant*inc01X) + indEchant*(((p1->getX()+indEchant*inc12X) - (p0->getX()+indEchant*inc01X))/echant);
            double posY = (p0->getY()+indEchant*inc01Y) + indEchant*(((p1->getY()+indEchant*inc12Y) - (p0->getY()+indEchant*inc01Y))/echant);

            posOutput = i*this->nbProjectedPoints+indEchant;
            outputTraj->trajectory->at(posOutput)->setX(posX);
            outputTraj->trajectory->at(posOutput)->setY(posY);
            for (unsigned int ii=1; ii<trajectory->trajectory->size(); ii++) {
                    if (tempVectForTimestamp[(ii-1)]["watchdog"] < 10) {
                        double distTmp = geoMetrics::distanceTo(outputTraj->trajectory->at(posOutput), trajectory->trajectory->at(ii), this->dataRef);
                        if (tempVectForTimestamp[(ii-1)]["minDist"] == -1 || distTmp <= tempVectForTimestamp[(ii-1)]["minDist"]) {
                            tempVectForTimestamp[(ii-1)]["minDist"] = distTmp;
                            tempVectForTimestamp[(ii-1)]["index"] = posOutput;
                        } else {
                            tempVectForTimestamp[(ii-1)]["watchdog"]++;
                        }
                    }
                }
        }
        p0 = outputTraj->trajectory->at(posOutput);
        objectives.pop_front();
    }
    objectives.clear();
    this->redresseTimestamp(&tempVectForTimestamp, trajectory, outputTraj.get());
    return outputTraj;
}

/**
 * \brief 	Generates the Cox-De Boor recursion algorithm for computing B-spline approximation
 *
 * \param 	knots           The list of control points
 * \param   knotSpanI       The range of the knot
 * \param   splineOrder     The spline order of the B-spline approximation
 * \param   projectedKnotU  The knot projected
 * \param   splineOrder The order of the spline (default=3)
 * \return 	The coefficient obtained for the input knot
 */
double Bspline::CoxDeBoorRecursion(std::vector<double>* knots, int knotSpanI, int splineOrder, double projectedKnotU) {
    if (splineOrder <= 1) {
        if (knots->at(knotSpanI) <= projectedKnotU && projectedKnotU < knots->at(knotSpanI+1)) return 1.0;
        return 0.0;
    }

    double num1 = projectedKnotU - knots->at(knotSpanI);
    double denom1 = knots->at(knotSpanI+splineOrder-1) - knots->at(knotSpanI);
    double num2 = knots->at(knotSpanI+splineOrder) - projectedKnotU;
    double denom2 = knots->at(knotSpanI+splineOrder) - knots->at(knotSpanI+1);

    double basisF1 = 0.0;
    double basisF2 = 0.0;

    if (denom1 != 0.0) basisF1 = (num1/denom1)*this->CoxDeBoorRecursion(knots, knotSpanI, splineOrder-1, projectedKnotU);
    if (denom2 != 0.0) basisF2 = (num2/denom2)*this->CoxDeBoorRecursion(knots, knotSpanI+1, splineOrder-1, projectedKnotU);
    return basisF1+basisF2;
}

/**
 * \brief 	Sets the timestamps of the projected points in the ouputTraj Trajectory according to the input trajectory reference points
 *
 * \param   tempVectForTimestamp    The vector that holds the timestamp references
 * \param 	trajectory              The reference Trajectory
 * \param 	ouputTraj               The Trajectory to rectify
 * \return 	None
 *
 * The timestamps of the projected points are set with equal repartition between two reference points
 */
void Bspline::redresseTimestamp(std::vector<std::map<std::string, double> >* tempVectForTimestamp, Trajectory* trajectory, Trajectory* outputTraj) {
    int lastStart = 0;
    for (unsigned int indCtrlPts=0; indCtrlPts<tempVectForTimestamp->size(); indCtrlPts++) {
        int indProjPt = tempVectForTimestamp->at(indCtrlPts)["index"];

        TemporalGeoPoint* p0 = trajectory->trajectory->at(indCtrlPts);
        TemporalGeoPoint* p1 = trajectory->trajectory->at(indCtrlPts+1);

        int nbCreneaux = indProjPt - lastStart;
        if (nbCreneaux > 0) {
            int incBas = (p1->timestamp - p0->timestamp)/nbCreneaux;
            int incHaut = incBas+1;

            int maxBasOcc = (incHaut*nbCreneaux - (p1->timestamp - p0->timestamp));
            int maxHautOcc = nbCreneaux - maxBasOcc;

            int incBasOcc = 0;
            int incHautOcc = 0;
            double lastTime = p0->timestamp;

            for (int i=lastStart+1; i<indProjPt+1; i++) {
                int addInc = incBas;
                if (i%2 == 0) {
                    if (incHautOcc < maxHautOcc) {
                        addInc = incHaut;
                        incHautOcc++;
                    } else {
                        incBasOcc++;
                    }
                } else {
                    if (incBasOcc < maxBasOcc) {
                        incBasOcc++;
                    } else {
                        addInc = incHaut;
                        incHautOcc++;
                    }
                }
                double currentTime = lastTime+addInc;

                outputTraj->trajectory->at(i)->timestamp = currentTime;
                lastTime = currentTime;
            }
        }
        lastStart = indProjPt;
    }
}
