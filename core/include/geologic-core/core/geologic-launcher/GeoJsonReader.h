/**
 * \file	GeoJsonReader.h
 */

#ifndef GeoJsonReader_H
#define GeoJsonReader_H

#include "shapefil.h"
#include "geologic-core/core/geologic-launcher/CoordinateSystemManager.h"
#include "geologic-core/objects/dynamic/MobileObject.h"
#include "geologic-core/objects/dynamic/Trajectory.h"
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QFile>
#include <QtOpenGL/QtOpenGL>
#include <string>
#include <vector>


class GeoJsonReader {

    public:
        //*/ -------------------------------------------------
        static GeoJsonReader* getInstance();

        //*/ -------------------------------------------------
        void load(std::string fileName, OGRSpatialReference* gpxCSreading, OGRSpatialReference* gpxCSdestination=nullptr);
        //OGRMultiPoint* getPoints();
        MobileObject* getMobile();

    private:
        //*/ -------------------------------------------------
        GeoJsonReader();

        //*/ -------------------------------------------------
        GeoJsonReader(GeoJsonReader const&) = delete;
        void operator = (GeoJsonReader const&) = delete;

        //*/ -------------------------------------------------
        void clean();
        void parseSegment(QXmlStreamReader& reader);
        TemporalGeoPoint* parsePoint(QXmlStreamReader& reader);

        //*/ -------------------------------------------------
        static GeoJsonReader* instance;
        //OGRMultiPoint* points;
        MobileObject* mobile;
        Trajectory* trajectory;
        unsigned int idx;

        OGRSpatialReference* gpxCSreading;
        OGRSpatialReference* gpxCSdestination;
};

#endif // GeoJsonReader_H
