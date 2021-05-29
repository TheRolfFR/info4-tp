/**
 * \file	Displacement.h
 */

#ifndef DISPLACEMENT_H
#define DISPLACEMENT_H

#include "geologic-core/graphicTemplates/GeologicCustomizeObject.h"
#include "geologic-core/graphicTemplates/GeologicGraphicalObjectMobile.h"
#include <vector>
#include <string>
#include <ogr_geometry.h>
#include "geologic-core/objects/dynamic/Trip.h"


class Displacement : public GeologicGraphicalObjectMobile, public GeologicCustomizeObject {

    public:
        //*/ -------------------------------------------------
        Displacement();
        virtual ~Displacement();

        Displacement(Displacement* displacement);
        Displacement(TemporalGeoZone* zoneOrigin, TemporalGeoZone* zoneDestination, std::string reason);

        //*/ -------------------------------------------------
        virtual std::unique_ptr<OGRPoint> display(double timestamp);
        virtual std::unique_ptr<OGRPoint> display(double timestamp, int splineOrder);
        virtual std::unique_ptr<OGRPoint> display(double timestamp, std::string approximationAlgorithmName, double factor=0.75);
        virtual std::unique_ptr<OGRPoint> display(double timestamp, std::unordered_map<std::string, GeoZone*>* zones);

        //*/ -------------------------------------------------
        TemporalGeoZone* zoneOrigin;
        TemporalGeoZone* zoneDestination;
        time_t displacementDuration;
        std::vector<Trip*> trips;
        std::string mainReason;

    private:
        //*/ -------------------------------------------------
        std::unique_ptr<OGRPoint> computeDisplayPoint(double timestamp, Trajectory* approximationTrajectory);
        bool hasChanged();

        //*/ -------------------------------------------------
        unsigned int lastTripsSize;
};

#endif // DISPLACEMENT_H
