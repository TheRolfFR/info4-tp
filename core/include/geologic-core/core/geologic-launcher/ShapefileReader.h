/**
 * \file	ShapefileReader.h
 */

#ifndef ShapefileReader_H
#define ShapefileReader_H

#include "shapefil.h"
#include <string>
#include <vector>
#include "geologic-core/objects/geo/untemporal/GeoZone.h"


class ShapefileReader {

    public:
        //*/ -------------------------------------------------
        static ShapefileReader* getInstance();

        //*/ -------------------------------------------------
        void load(std::string fileName, OGRSpatialReference* shapefileCSreading, OGRSpatialReference* shapefileCSdestination=nullptr);
        std::vector<GeoZone*>* getShapes();
        std::vector<std::vector<std::string>* >* getRecords();
        std::vector<std::string>* getRecordsFields();
        OGRMultiPoint* getPoints();

    private:
        //*/ -------------------------------------------------
        ShapefileReader();

        //*/ -------------------------------------------------
        ShapefileReader(ShapefileReader const&) = delete;
        void operator = (ShapefileReader const&) = delete;

        //*/ -------------------------------------------------
        void clean();

        //*/ -------------------------------------------------
        static ShapefileReader* instance;
        std::vector<GeoZone*>* shapes;
        std::vector<std::vector<std::string>* >* records;
        std::vector<std::string>* recordsFields;
        OGRMultiPoint* points;
};

#endif // ShapefileReader_H
