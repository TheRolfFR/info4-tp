/**
 * \file	Trip.h
 */

#ifndef TRIP_H
#define TRIP_H

#include "geologic-core/graphicTemplates/GeologicGraphicalObjectMobile.h"
#include "geologic-core/graphicTemplates/GeologicCustomizeObject.h"
#include <vector>
#include <time.h>
#include <ogr_geometry.h>
#include "geologic-core/objects/transportation/TransportationType.h"
#include "geologic-core/objects/geo/temporal/TemporalGeoZone.h"
#include "geologic-core/superClasses/Metadata.h"


class Trip : public GeologicGraphicalObjectMobile, public GeologicCustomizeObject {

    public:
        //*/ -------------------------------------------------
        Trip();
        virtual ~Trip();

        Trip(Trip* trip);
        Trip(TemporalGeoZone* zoneOrigin, TemporalGeoZone* zoneDestination, TransportationType* type=nullptr);

        //*/ -------------------------------------------------
        void computeDuration();
        void printTrip();
        virtual std::unique_ptr<OGRPoint> display(double timestamp);
        virtual std::unique_ptr<OGRPoint> display(double timestamp, int splineOrder);
        virtual std::unique_ptr<OGRPoint> display(double timestamp, std::string approximationAlgorithmName, double factor=0.75);
        virtual std::unique_ptr<OGRPoint> display(double timestamp, std::unordered_map<std::string, GeoZone*>* zones);

        //*/ -------------------------------------------------
        TemporalGeoZone* zoneOrigin;
        TemporalGeoZone* zoneDestination;
        TransportationType* type;
        time_t tripDuration;
};

#endif // TRIP_H
