/**
 * \file	CoordinateSystemManager.h
 */

#ifndef COORDINATESYSTEMMANAGER_H
#define COORDINATESYSTEMMANAGER_H

#include <memory>
#include <ogr_spatialref.h>
#include <ogr_geometry.h>
#include "geologic-core/core/geologic-mapper/geo/CoordinateSystemMap.h"
#include "geologic-core/core/geologic-mapper/geo/CoordinateTransformationMap.h"
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Constants.hpp>


class CoordinateSystemManager {

    public:
        //*/ -------------------------------------------------
        static CoordinateSystemManager* getInstance();

        //*/ -------------------------------------------------
        OGRSpatialReference* getDataRef();
        OGRSpatialReference* getViewRef();
        OGRSpatialReference* getDisplayRef();

        //*/ -------------------------------------------------
        void setReferences(OGRSpatialReference* dataRef, OGRSpatialReference* viewRef, OGRSpatialReference* displayRef);
        void setDataRef(OGRSpatialReference* dataRef);
        void setViewRef(OGRSpatialReference* viewRef);
        void setDisplayRef(OGRSpatialReference* displayRef);

        //*/ -------------------------------------------------
        OGRSpatialReference* getCSbyName(std::string csName);
        std::unique_ptr<OGRSpatialReference> getCSbyRef(std::string csRef);
        std::string getCSName(OGRSpatialReference* csr);

        //*/ -------------------------------------------------
        std::unique_ptr<CoordinateSystemMap> cooSysMapper;
        std::unique_ptr<CoordinateTransformationMap> cooTraMapper;
        std::unique_ptr<GeographicLib::Geodesic> geod;

    private:
        //*/ -------------------------------------------------
        CoordinateSystemManager();

        //*/ -------------------------------------------------
        CoordinateSystemManager(CoordinateSystemManager const&) = delete;
        void operator = (CoordinateSystemManager const&) = delete;

        //*/ -------------------------------------------------
        static CoordinateSystemManager* instance;

        //*/ -------------------------------------------------
        std::unique_ptr<OGRSpatialReference> dataRef; ///< Reference used in data
        std::unique_ptr<OGRSpatialReference> viewRef; ///< Reference used in OpenGL View
        std::unique_ptr<OGRSpatialReference> displayRef; ///< Reference used for displaying in status bar
};

#endif // COORDINATESYSTEMMANAGER_H
