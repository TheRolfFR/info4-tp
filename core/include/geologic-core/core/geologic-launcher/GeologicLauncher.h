/**
 * \file	GeologicLauncher.h
 */

#ifndef GEOLOGICLAUNCHER_H
#define GEOLOGICLAUNCHER_H

#include <string>
#include "geologic-core/core/geologic-mapper/GeologicMapper.h"
#include "geologic-core/core/geologic-launcher/CoordinateSystemManager.h"
#include "geologic-core/core/geologic-launcher/ShapefileReader.h"


class GeologicLauncher {

	public:
        //*/ -------------------------------------------------
        static GeologicLauncher* getInstance();

    private:
        //*/ -------------------------------------------------
        GeologicLauncher();

        //*/ -------------------------------------------------
        GeologicLauncher(GeologicLauncher const&) = delete;
        void operator = (GeologicLauncher const&) = delete;

        //*/ -------------------------------------------------
        void parseUtils();

        //*/ -------------------------------------------------
        static GeologicLauncher* instance;
        CoordinateSystemManager* csManager;
        GeologicMapper* mapper;
        ShapefileReader* shapefileReader;
};

#endif //GEOLOGICLAUNCHER_H
