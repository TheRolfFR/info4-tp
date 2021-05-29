/**
 * \file	Bspline.h
 */

#ifndef Bspline_H
#define Bspline_H

#include <vector>
#include <string>
#include <deque>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <memory>
#include "geologic-core/utils/customToolbox.h"
#include "geologic-core/objects/geo/untemporal/GeoZone.h"
#include "geologic-core/objects/dynamic/Trajectory.h"
#include "geologic-core/graphicTemplates/GeologicGeometricalObject.h"


class Bspline {

    public:
        //*/ -------------------------------------------------
        Bspline();
        virtual ~Bspline();

        Bspline(int nbProjectedPoints);

        //*/ -------------------------------------------------
        //double computeEuclideanDistance(Edge* edge);

        double computeEuclideanDistance(Trajectory* trajectory);
        double computeBsplineDistance(Trajectory* trajectory, int splineOrder=3);
        double computeGravityLikeModelDistance(Trajectory* trajectory, double glmFactor=0.75);
        double computeSmoothedBsplineDistance(Trajectory* trajectory, double sbFactor=0.5);
        double computeFixedBsplineRoundedModelDistance(Trajectory* trajectory, double fbrFactor=0.6);
        double computeAutomaticBsplineRoundedModelDistance(Trajectory* trajectory, std::unordered_map<std::string, GeoZone*>* zones);

        //*/ -------------------------------------------------
        std::unique_ptr<Trajectory> computeEuclideanTrajectory(Trajectory* trajectory);
        std::unique_ptr<Trajectory> computeBsplineTrajectory(Trajectory* trajectory, int splineOrder);
        std::unique_ptr<Trajectory> computeGravityLikeModelTrajectory(Trajectory* trajectory, double glmFactor);
        std::unique_ptr<Trajectory> computeSmoothedBsplineTrajectory(Trajectory* trajectory, double sbFactor);
        std::unique_ptr<Trajectory> computeFixedBsplineRoundedModelTrajectory(Trajectory* trajectory, double fbrFactor);
        std::unique_ptr<Trajectory> computeAutomaticBsplineRoundedModelTrajectory(Trajectory* trajectory, std::unordered_map<std::string, GeoZone*>* zones);

        //*/ -------------------------------------------------
        void setDataRef(OGRSpatialReference* dataRef);
        OGRSpatialReference* getDataRef();

    private:
        //*/ -------------------------------------------------
        double CoxDeBoorRecursion(std::vector<double>* knots, int knotSpanI, int splineOrder, double projectedKnotU);
        void redresseTimestamp(std::vector<std::map<std::string, double> >* tempVectForTimestamp, Trajectory* trajectory, Trajectory* outputTraj);

        //*/ -------------------------------------------------
        OGRSpatialReference* dataRef;
        int nbProjectedPoints;
};

#endif // Bspline_H
