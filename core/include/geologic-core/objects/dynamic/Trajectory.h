/**
 * \file	Trajectory.h
 */

#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <ogr_geometry.h>
#include "geologic-core/graphicTemplates/GeologicGraphicalObjectMobile.h"
#include "geologic-core/objects/transportation/TransportationType.h"
#include "geologic-core/objects/geo/temporal/TemporalGeoPoint.h"
#include "geologic-core/objects/geo/untemporal/GeoZone.h"


class Trajectory : public GeologicGraphicalObjectMobile {

    public:
        //*/ -------------------------------------------------
        Trajectory();
        virtual ~Trajectory();

        Trajectory(Trajectory* trajectory);
        Trajectory(std::vector<TemporalGeoPoint*>* trajectory, TransportationType* transportationType);

        //*/ -------------------------------------------------
        void addPosition(TemporalGeoPoint* position);
        void insertPosition(TemporalGeoPoint* position);
        std::unique_ptr<TemporalGeoPoint> getClosestPoint(double timestamp);
        std::unique_ptr<TemporalGeoPoint> getNewPositionAt(double timestamp);

        //*/ -------------------------------------------------
        void dummyFill(int slotDuration);
        unsigned int size();
        void clear(bool hard);

        //*/ -------------------------------------------------
        virtual std::unique_ptr<OGRPoint> display(double timestamp);
        virtual std::unique_ptr<OGRPoint> display(double timestamp, int splineOrder);
        virtual std::unique_ptr<OGRPoint> display(double timestamp, std::string approximationAlgorithmName, double factor=0.75);
        virtual std::unique_ptr<OGRPoint> display(double timestamp, std::unordered_map<std::string, GeoZone*>* zones);

        //*/ -------------------------------------------------
        std::vector<TemporalGeoPoint*>* trajectory;
        TransportationType* transportationType;

    private:
        //*/ -------------------------------------------------
        bool hasChanged();
        std::unique_ptr<OGRPoint> computeDisplayPoint(double timestamp, Trajectory* approximationTrajectory);

        //*/ -------------------------------------------------
        unsigned int lastTrajectorySize;
};

#endif // TRAJECTORY_H
