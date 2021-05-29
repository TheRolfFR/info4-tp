/**
 * \file	GPXReader.h
 */

#ifndef GPXReader_H
#define GPXReader_H

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


class GPXReader {

    public:
        //*/ -------------------------------------------------
        static GPXReader* getInstance();

        //*/ -------------------------------------------------
        void load(std::string fileName, OGRSpatialReference* gpxCSreading, OGRSpatialReference* gpxCSdestination=nullptr);
        //OGRMultiPoint* getPoints();
        MobileObject* getMobile();

    private:
        //*/ -------------------------------------------------
        GPXReader();

        //*/ -------------------------------------------------
        GPXReader(GPXReader const&) = delete;
        void operator = (GPXReader const&) = delete;

        //*/ -------------------------------------------------
        void clean();
        void parseSegment(QXmlStreamReader& reader);
        TemporalGeoPoint* parsePoint(QXmlStreamReader& reader);

        //*/ -------------------------------------------------
        static GPXReader* instance;
        //OGRMultiPoint* points;
        MobileObject* mobile;
        Trajectory* trajectory;
        unsigned int idx;

        OGRSpatialReference* gpxCSreading;
        OGRSpatialReference* gpxCSdestination;
};

#endif // GPXReader_H
