/**
 * \file	GPXReader.cpp
 * \class	GPXReader
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Reads and create shapes from a GPX object
 *
 * \details This class contains the main methods used to read and parse a GPX file
 */

#include "geologic-core/core/geologic-launcher/GPXReader.h"
#include "geologic-core/utils/customToolbox.h"
#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"

using namespace std;
using namespace customToolbox;


GPXReader* GPXReader::instance = 0;

/**
 * \brief 	Default constructor of class GPXReader
 *
 * \param 	None
 * \return 	None
 */
GPXReader::GPXReader() {
    //this->points = new OGRMultiPoint();
    idx = 0;
    this->mobile = new MobileObject();
    this->trajectory = nullptr;
    this->gpxCSreading = CoordinateSystemManager::getInstance()->getDataRef();
    this->gpxCSdestination = CoordinateSystemManager::getInstance()->getDataRef();
}

/**
 * \brief 	Returns the instance of the GPXReader singleton
 *
 * \param 	None
 * \return 	The reference of the GPXReader singleton
 */
GPXReader* GPXReader::getInstance() {
    if (!instance) {
        instance = new GPXReader;
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
void GPXReader::parseSegment(QXmlStreamReader& reader) {
    QXmlStreamReader::TokenType tok = reader.readNext();
    while (!reader.atEnd() && !reader.hasError() /*&& tok != QXmlStreamReader::EndElement*/) {
        if (reader.name().toString() == "trkpt") {
            TemporalGeoPoint* tgp = parsePoint(reader);
            trajectory->addPosition(tgp);
            delete tgp;
            tgp = nullptr;
        }
//        else
        tok = reader.readNext();
//        cout << reader.name().toString().toStdString() << endl;
        if (tok == QXmlStreamReader::EndElement && reader.name().toString() == "trkseg") {
            trajectory = new Trajectory();
            mobile->listTrajectories.insert(pair<string, Trajectory*>(str(idx++), trajectory));
            break;
        }
    }
}

/**
 * \brief 	Opens a shapefile object and parses the main structures into shapes and records maps
 *
 * \param 	fileName                The name of the file to open as an ESRI shapefile
 * \param   shapefileCSreading      The CoordinateSystem of the input ESRI file
 * \param   shapefileCSDestination  The CoordinateSystem used to convert the final GeoZone
 * \return 	None
 */
TemporalGeoPoint* GPXReader::parsePoint(QXmlStreamReader& reader) {
    TemporalGeoPoint* tgp = new TemporalGeoPoint();
    QXmlStreamReader::TokenType tok = reader.tokenType();
    while (!reader.atEnd() && !reader.hasError() /*&& tok != QXmlStreamReader::EndElement*/) {
        if (reader.name().toString() == "trkpt") {
            tgp->setX(reader.attributes().value("lon").toDouble());
            tgp->setY(reader.attributes().value("lat").toDouble());
            geoMetrics::convertTo(tgp, gpxCSreading, gpxCSdestination);
        } else if (reader.name().toString() == "time" && tok == QXmlStreamReader::StartElement) {
            tok = reader.readNext();
            //tgp.timestamp = QDateTime::fromString(reader.text().toString(), "yyyy-MM-ddThh:mm:ssZ");
            tgp->timestamp = str2timet(reader.text().toString().toStdString(), "YYYY-MM-DD HH:MM:SS");
        }
        tok = reader.readNext();
        if (tok == QXmlStreamReader::EndElement && reader.name().toString() == "trkpt") {
            break;
        }
    }
    return tgp;
}

/**
 * \brief 	Opens a shapefile object and parses the main structures into shapes and records maps
 *
 * \param 	fileName                The name of the file to open as an ESRI shapefile
 * \param   shapefileCSreading      The CoordinateSystem of the input ESRI file
 * \param   shapefileCSDestination  The CoordinateSystem used to convert the final GeoZone
 * \return 	None
 */
void GPXReader::load(std::string fileName, OGRSpatialReference* gpxCSreading, OGRSpatialReference* gpxCSdestination) {
    //this->clean();
    this->gpxCSreading = gpxCSreading;
    this->gpxCSdestination = gpxCSdestination;

    QFile f(QString::fromStdString(fileName));
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QXmlStreamReader reader(&f);
    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType tok = reader.readNext();
        if (tok == QXmlStreamReader::StartElement) {
            if (reader.name().toString() == "trkseg") {
                trajectory = new Trajectory();
                mobile->listTrajectories.insert(pair<string, Trajectory*>(str(idx++), trajectory));
                parseSegment(reader);
            } else {
                tok = reader.readNext();
            }
        }
    }

    //*/ -------------------------------------------------
    /*/
                OGRPoint tempPoint = OGRPoint(currentX, currentY, currentZ, currentM);
                geoMetrics::convertTo(&tempPoint, gpxCSreading, gpxCSdestination);
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


            newZone->addGeometry(&subZone);

            if (subZone.get_Area() >= maxArea) {
                newZone->setMainZone(newZone->getNumGeometries()-1);
                maxArea = subZone.get_Area();
            }
            newZone->setBbox();
            this->shapes->push_back(newZone);
        } else if (shapeType == 1) {

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
                geoMetrics::convertTo(&tempPoint, gpxCSreading, gpxCSdestination);

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

    //*/

}

/**
 * \brief 	Cleans the GPXReader main objects (shapes, records, points, etc.)
 *
 * \param 	None
 * \return 	None
 */
void GPXReader::clean() {
    //this->points->empty();
    delete this->trajectory;
    trajectory = nullptr;
}

/**
 * \brief 	Returns the points of the shapefile as a OGRMultiPoint (to use after loading a file first)
 *
 * \param 	None
 * \return 	A reference of an OGRMultiPoint
 */
//OGRMultiPoint* GPXReader::getPoints() {
 //   return points;
//}

/**
 * \brief 	Returns the points of the shapefile as a OGRMultiPoint (to use after loading a file first)
 *
 * \param 	None
 * \return 	A reference of an OGRMultiPoint
 */
MobileObject* GPXReader::getMobile() {
    return mobile;
}

