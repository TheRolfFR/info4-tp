/**
 * \file	TrajectoryManager.h
 */

#ifndef TRAJECTORYMANAGER_H
#define TRAJECTORYMANAGER_H

#include "geologic-core/objects/dynamic/Trajectory.h"
#include "geologic-core/utils/customToolbox.h"
#include "geologic-core/core/geologic-launcher/CoordinateSystemManager.h"
#include <memory>


class TrajectoryManager {

    public:
        //*/ -------------------------------------------------
        TrajectoryManager();
        virtual ~TrajectoryManager();

        //*/ -------------------------------------------------
        std::unique_ptr<Trajectory> dayFilling(Trajectory* trajectory, int slotDuration, std::string strategy);
        std::unique_ptr<std::vector<std::unique_ptr<Trajectory> > > extractTrips(Trajectory* trajectory, int stopDuration,
                                               double significantDistance, OGRSpatialReference* dataRef=CoordinateSystemManager::getInstance()->getDataRef());

        std::unique_ptr<Trajectory> cleanTrajectory(Trajectory* Trajectory, double significantDistance,
                                    OGRSpatialReference* dataRef=CoordinateSystemManager::getInstance()->getDataRef());

        void cleanTrajectory(Trajectory& Trajectory, double significantDistance,
                             OGRSpatialReference* dataRef=CoordinateSystemManager::getInstance()->getDataRef());

        void infos(Trajectory* trajectory);
        void order(Trajectory* trajectory);
};

#endif // TRAJECTORYMANAGER_H
