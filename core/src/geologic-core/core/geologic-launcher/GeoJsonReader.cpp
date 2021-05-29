/**
 * \file	GeoJsonReader.cpp
 * \class	GeoJsonReader
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Reads and create shapes from a GPX object
 *
 * \details This class contains the main methods used to read and parse a GPX file
 */

#include "geologic-core/core/geologic-launcher/GeoJsonReader.h"
#include "geologic-core/utils/customToolbox.h"
#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"

using namespace std;
using namespace customToolbox;


GeoJsonReader* GeoJsonReader::instance = 0;

/**
 * \brief 	Default constructor of class GeoJsonReader
 *
 * \param 	None
 * \return 	None
 */
GeoJsonReader::GeoJsonReader() {
    //this->points = new OGRMultiPoint();
    idx = 0;
    this->mobile = new MobileObject();
    this->trajectory = nullptr;
    this->gpxCSreading = CoordinateSystemManager::getInstance()->getDataRef();
    this->gpxCSdestination = CoordinateSystemManager::getInstance()->getDataRef();
}

/**
 * \brief 	Returns the instance of the GeoJsonReader singleton
 *
 * \param 	None
 * \return 	The reference of the GeoJsonReader singleton
 */
GeoJsonReader* GeoJsonReader::getInstance() {
    if (!instance) {
        instance = new GeoJsonReader;
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
void GeoJsonReader::parseSegment(QXmlStreamReader& reader) {
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
TemporalGeoPoint* GeoJsonReader::parsePoint(QXmlStreamReader& reader) {
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
void GeoJsonReader::load(std::string fileName, OGRSpatialReference* gpxCSreading, OGRSpatialReference* gpxCSdestination) {
    this->clean();
    this->gpxCSreading = gpxCSreading;
    this->gpxCSdestination = gpxCSdestination;

    QFile f(QString::fromStdString(fileName));
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QString val = f.readAll();
    f.close();

    QJsonDocument wholeDocument = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObjOfWholeDocument = wholeDocument.object();

    QJsonArray arrayOfFeatures = jsonObjOfWholeDocument["features"].toArray();
    QJsonObject arrayOfFeaturesAsObject = arrayOfFeatures[0].toObject();
    QJsonObject geometryObject = arrayOfFeaturesAsObject["geometry"].toObject();
    QJsonArray coordinates = geometryObject["coordinates"].toArray();


    trajectory = new Trajectory();
    mobile->listTrajectories.insert(pair<string, Trajectory*>(str(idx++), trajectory));
    //parseSegment(reader);

    for (int i=0; i<coordinates.size(); i++) {
        QJsonArray coords = coordinates[i].toArray();

        TemporalGeoPoint* tgp = new TemporalGeoPoint(coords[0].toDouble(), coords[1].toDouble(), 0, i);
        geoMetrics::convertTo(tgp, gpxCSreading, gpxCSdestination);
        trajectory->addPosition(tgp);
    }
}

/**
 * \brief 	Cleans the GeoJsonReader main objects (shapes, records, points, etc.)
 *
 * \param 	None
 * \return 	None
 */
void GeoJsonReader::clean() {
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
//OGRMultiPoint* GeoJsonReader::getPoints() {
 //   return points;
//}

/**
 * \brief 	Returns the points of the shapefile as a OGRMultiPoint (to use after loading a file first)
 *
 * \param 	None
 * \return 	A reference of an OGRMultiPoint
 */
MobileObject* GeoJsonReader::getMobile() {
    return mobile;
}

