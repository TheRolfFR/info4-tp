/**
 * \file	GeoZone.h
 */

#ifndef GEOZONE_H
#define GEOZONE_H

#include "ogr_geometry.h"
#include <memory>
#include <string>
#include <unordered_map>
#include "geologic-core/graphicTemplates/GeologicCustomizeObject.h"
#include "geologic-core/objects/geo/untemporal/GeographicalObject.h"
#include "geologic-core/objects/geo/untemporal/Bbox.h"


class GeoZone : public OGRMultiPolygon, public GeographicalObject, public GeologicCustomizeObject {

    public:
        //*/ -------------------------------------------------
        GeoZone();
        virtual ~GeoZone();

        GeoZone(std::string name, std::unordered_map<std::string, std::string>* tags);
        GeoZone(GeoZone* zone);

        //*/ -------------------------------------------------
        bool display(double timestamp);
        bool display(double timestampOrigin, double timestampDestination);
        void setMainZone(int geomId);
        void setBbox();
        void detectMainZone();
        unsigned int getNumPoints();
        std::shared_ptr<OGRPoint> getPoint(unsigned int pointId);
        bool containsPoint(OGRPoint* point);

        //*/ -------------------------------------------------
        std::string name;
        OGRPolygon* mainZone;
        double area;
        Bbox bbox;
};

#endif // GEOZONE_H
