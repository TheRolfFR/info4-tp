/**
 * \file	GeologicGraphicalObjectMobile.h
 */

#ifndef GEOLOGICGRAPHICALOBJECTMOBILE_H
#define GEOLOGICGRAPHICALOBJECTMOBILE_H

#include <ogr_geometry.h>
#include "geologic-core/graphicTemplates/GeologicGraphicalObject.h"
#include "geologic-core/objects/geo/temporal/TemporalGeoPoint.h"
#include "geologic-core/objects/geo/untemporal/GeoZone.h"
#include <time.h>
#include <unordered_map>
#include <string>
#include <vector>


class Bspline;
class Trajectory;

class GeologicGraphicalObjectMobile : public GeologicGraphicalObject {

    public:
        //*/ -------------------------------------------------
        GeologicGraphicalObjectMobile();
        virtual ~GeologicGraphicalObjectMobile();

        //*/ -------------------------------------------------
        virtual std::unique_ptr<OGRPoint> display(double timestamp) = 0;
        virtual std::unique_ptr<OGRPoint> display(double timestamp, int splineOrder) = 0;
        virtual std::unique_ptr<OGRPoint> display(double timestamp, std::string approximationAlgorithmName, double factor=0.75) = 0;
        virtual std::unique_ptr<OGRPoint> display(double timestamp, std::unordered_map<std::string, GeoZone*>* zones) = 0;
        void setType();

    protected:
        //*/ -------------------------------------------------
        std::unique_ptr<Bspline> bsplineModule;
        std::unordered_map<std::string, Trajectory*> mapCacheTrajectories;
};

#endif // GEOLOGICGRAPHICALOBJECTMOBILE_H
