/**
 * \file	ShapefileReader.cpp
 * \class	ShapefileReader
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Reads and create shapes from a shapefile object
 *
 * \details This class contains the main methods used to read and parse a shapefile object
 */

#include "geologic-core/core/geologic-launcher/ShapefileReader.h"
#include "geologic-core/utils/customToolbox.h"
#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"

using namespace std;
using namespace customToolbox;


ShapefileReader* ShapefileReader::instance = 0;

/**
 * \brief 	Default constructor of class ShapefileReader
 *
 * \param 	None
 * \return 	None
 */
ShapefileReader::ShapefileReader() {
    this->shapes = new vector<GeoZone*>();
    this->records = new vector<vector<string>* >();
    this->recordsFields = new vector<string>();
    this->points = new OGRMultiPoint();
}

/**
 * \brief 	Returns the instance of the ShapefileReader singleton
 *
 * \param 	None
 * \return 	The reference of the ShapefileReader singleton
 */
ShapefileReader* ShapefileReader::getInstance() {
    if (!instance) {
        instance = new ShapefileReader;
    }
    return instance;
}

/**
 * \brief 	Opens a shapefile object and parses the main structures into shapes and records maps
 *
 * \param 	fileName                The name of the file to open as an ESRI shapefile
 * \param   shapefileCSreading      The CoordinateSystem of the input ESRI file
 * \param   shapefileCSDestination  The CoordinateSystem used to convert the final GeoZone
 * \return 	None
 */
void ShapefileReader::load(std::string fileName, OGRSpatialReference* shapefileCSreading, OGRSpatialReference* shapefileCSdestination) {
    this->clean();

    //*/ -------------------------------------------------
    /*/
    2D Shape Types (pre ArcView 3.x):
        #define SHPT_POINT		    1	Points
        #define SHPT_ARC		    3	Arcs (Polylines, possible in parts)
        #define SHPT_POLYGON	    5	Polygons (possible in parts)
        #define SHPT_MULTIPOINT	    8	MultiPoint (related points)
    3D Shape Types (may include "measure" values for vertices):
        #define SHPT_POINTZ		    11
        #define SHPT_ARCZ		    13
        #define SHPT_POLYGONZ		15
        #define SHPT_MULTIPOINTZ 	18
    2D + Measure Types:
        #define SHPT_POINTM		    21
        #define SHPT_ARCM		    23
        #define SHPT_POLYGONM		25
        #define SHPT_MULTIPOINTM 	28
    Complex (TIN-like) with Z, and Measure:
        #define SHPT_MULTIPATCH 	31
    //*/

    //*/ -------------------------------------------------
    SHPHandle shapesH = SHPOpen(fileName.c_str(), "rb");
    DBFHandle recordsH = DBFOpen(fileName.c_str(), "rb");

    //*/ -------------------------------------------------
    int recordsNumber = DBFGetRecordCount(recordsH);
    int fieldsNumber = DBFGetFieldCount(recordsH);
    for (int field=0; field<fieldsNumber; field++) {
        char fieldName[12];
        DBFGetFieldInfo(recordsH, field, fieldName, nullptr, nullptr);
        recordsFields->push_back(fieldName);
    }

    //*/ -------------------------------------------------
    for (int indexShape=0; indexShape<recordsNumber; indexShape++) {
        vector<string>* fieldsValues = new vector<string>();
        for (int field=0; field<fieldsNumber; field++)
            fieldsValues->push_back(DBFReadStringAttribute(recordsH, indexShape, field));
        this->records->push_back(fieldsValues);

        SHPObject* tempShape = SHPReadObject(shapesH, indexShape);
        int shapeType = tempShape->nSHPType;
        int vertexNumber = tempShape->nVertices;
        int nbParts = tempShape->nParts;
        double* xs = tempShape->padfX;
        double* ys = tempShape->padfY;
        double* zs = tempShape->padfZ;
        double* ms = tempShape->padfM;

        //*/ -------------------------------------------------
        if (shapeType == 5) {
            GeoZone* newZone = new GeoZone; //many polygons
            OGRLinearRing way;
            OGRPolygon subZone; //1 inner and n outers
            double maxArea = 0.0;

            //*/ -------------------------------------------------
            int nextStart = vertexNumber;
            int currentPart = 1;
            if (nbParts > 1) nextStart = *(++tempShape->panPartStart);
            for (int inc=0; inc<vertexNumber; inc++) {
                double currentX = *(xs++);
                double currentY = *(ys++);
                double currentZ = 0.0;
                if (zs != nullptr) currentZ = *(zs++);
                double currentM = 0.0;
                if (ms != nullptr) currentM = *(ms++);
                OGRPoint tempPoint = OGRPoint(currentX, currentY, currentZ, currentM);
                geoMetrics::convertTo(&tempPoint, shapefileCSreading, shapefileCSdestination);
                way.addPoint(&tempPoint);

                if (inc == (nextStart-1)) {
                    if (!bool(way.get_IsClosed())) way.closeRings();
                    if (!subZone.IsEmpty() && way.isClockwise()) {
                        newZone->addGeometry(&subZone);
                        if (subZone.get_Area() >= maxArea) {
                            newZone->setMainZone(newZone->getNumGeometries()-1);
                            maxArea = subZone.get_Area();
                        }
                        subZone.empty();
                    }

                    subZone.addRing(&way);
                    way.empty();

                    nextStart = vertexNumber;
                    if (++currentPart < nbParts) {
                        nextStart = *(++tempShape->panPartStart);
                    }
                }
            }

            //*/ -------------------------------------------------
            newZone->addGeometry(&subZone);

            if (subZone.get_Area() >= maxArea) {
                newZone->setMainZone(newZone->getNumGeometries()-1);
                maxArea = subZone.get_Area();
            }
            newZone->setBbox();
            this->shapes->push_back(newZone);
        } else if (shapeType == 1) {
            //*/ -------------------------------------------------
            int nextStart = vertexNumber;
            int currentPart = 1;
            if (nbParts > 1) nextStart = *(++tempShape->panPartStart);
            for (int inc=0; inc<vertexNumber; inc++) {
                double currentX = *(xs++);
                double currentY = *(ys++);
                double currentZ = 0.0;
                if (zs != nullptr) currentZ = *(zs++);
                double currentM = 0.0;
                if (ms != nullptr) currentM = *(ms++);
                OGRPoint tempPoint = OGRPoint(currentX, currentY, currentZ, currentM);
                geoMetrics::convertTo(&tempPoint, shapefileCSreading, shapefileCSdestination);

                points->addGeometry(&tempPoint);

                if (inc == (nextStart-1)) {
                    nextStart = vertexNumber;
                    if (++currentPart < nbParts) {
                        nextStart = *(++tempShape->panPartStart);
                    }
                }
            }
        }
    }

    //*/ -------------------------------------------------
    SHPClose(shapesH);
    DBFClose(recordsH);
}

/**
 * \brief 	Cleans the ShapefileReader main objects (shapes, records, points, etc.)
 *
 * \param 	None
 * \return 	None
 */
void ShapefileReader::clean() {
    for (unsigned int indexShape=0; indexShape<shapes->size(); indexShape++) {
        delete(this->shapes->at(indexShape));
        delete(this->records->at(indexShape));
        this->shapes->at(indexShape) = nullptr;
        this->records->at(indexShape) = nullptr;
    }
    this->shapes->clear();
    this->records->clear();
    this->points->empty();
}

/**
 * \brief 	Returns the shapes of the shapefile as a vector of GeoZone (to use after loading a file first)
 *
 * \param 	None
 * \return 	A vector of GeoZone
 */
vector<GeoZone*>* ShapefileReader::getShapes() {
    return shapes;
}

/**
 * \brief 	Returns the reacords of the shapefile as a vector of String (to use after loading a file first)
 *
 * \param 	None
 * \return 	A vector of String
 */
vector<vector<string>* >* ShapefileReader::getRecords() {
    return records;
}

/**
 * \brief 	Returns the names of the records fields of the shapefile as a vector of String (to use after loading a file first)
 *
 * \param 	None
 * \return 	A vector of String
 */
vector<string>* ShapefileReader::getRecordsFields() {
    return recordsFields;
}

/**
 * \brief 	Returns the points of the shapefile as a OGRMultiPoint (to use after loading a file first)
 *
 * \param 	None
 * \return 	A reference of an OGRMultiPoint
 */
OGRMultiPoint* ShapefileReader::getPoints() {
    return points;
}

