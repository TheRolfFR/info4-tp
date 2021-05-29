/**
 * \file	GeologicLauncher.cpp
 * \class   GeologicLauncher
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Launches the first actions of the library
 *
 * \details Methods of GeologicLauncher object
 * This Launcher based on the Singleton design pattern. It will create an return an instance of a GeologicLauncher that contains
 * an instance of GeologicMapper, CoordinateSystemManager, ShapefileReader, etc.
 * This launcher is used to access the "map" structures of the library
 */

#include "geologic-core/core/geologic-launcher/GeologicLauncher.h"
#include "geologic-core/utils/customToolbox.h"

using namespace std;
using namespace customToolbox;

GeologicLauncher* GeologicLauncher::instance = 0;


/**
 * \brief 	Default constructor of class GeologicLauncher
 *
 * \param 	None
 * \return 	None
 */
GeologicLauncher::GeologicLauncher() {
    this->csManager = CoordinateSystemManager::getInstance();
    this->mapper = GeologicMapper::getInstance();
    this->shapefileReader = ShapefileReader::getInstance();
    this->parseUtils();
}

/**
 * \brief 	Returns the instance of the GeologicLauncher singleton
 *
 * \param 	None
 * \return 	The reference of the GeologicLauncher singleton
 */
GeologicLauncher* GeologicLauncher::getInstance() {
    if (!instance) {
        instance = new GeologicLauncher;
    }
    return instance;
}

/**
 * \brief 	Creates the main Geologic objects and stores them in the GeologicMapper, i.e, creates the main CoordinateSystemused in the library
 *
 * \param 	None
 * \return 	None
 */
void GeologicLauncher::parseUtils() {
    //WGS-84
    unique_ptr<OGRSpatialReference> cs_wgs84 = csManager->getCSbyRef("EPSG:4326");
    csManager->cooSysMapper->cooSysMap->insert(pair<string, shared_ptr<OGRSpatialReference>>(
                                                   "WGS 84", shared_ptr<OGRSpatialReference>(new OGRSpatialReference(*cs_wgs84)))); ///could be cs_wgs84->getName() ?

    //LambertIIe
    unique_ptr<OGRSpatialReference> cs_lambe = csManager->getCSbyRef("EPSG:27572");
    csManager->cooSysMapper->cooSysMap->insert(pair<string, shared_ptr<OGRSpatialReference>>(
                                                   "Lambert II etendu", shared_ptr<OGRSpatialReference>(new OGRSpatialReference(*cs_lambe))));

    //Lambert93
    unique_ptr<OGRSpatialReference> cs_lamb93 = csManager->getCSbyRef("EPSG:2154");
    csManager->cooSysMapper->cooSysMap->insert(pair<string, shared_ptr<OGRSpatialReference>>(
                                                   "Lambert 93", shared_ptr<OGRSpatialReference>(new OGRSpatialReference(*cs_lamb93))));

    //Pseudo mercator WGS84
    unique_ptr<OGRSpatialReference> cs_pm = csManager->getCSbyRef("EPSG:3857");
    csManager->cooSysMapper->cooSysMap->insert(pair<string, shared_ptr<OGRSpatialReference>>(
                                                   "WGS 84 Pseudo Mercator", shared_ptr<OGRSpatialReference>(new OGRSpatialReference(*cs_pm))));


    //Pseudo mercator OSGEO 41001
    string ogcwkt_osm = "PROJCS[\"WGS84 / Simple Mercator\", GEOGCS[\"OSM\", DATUM[\"WGS_1984\", SPHEROID[\"WGS_1984\",6378137,298.257223563]],";
    ogcwkt_osm += "PRIMEM[\"Greenwich\",0], UNIT[\"Decimal_Degree\", 0.0174532925199433]], PROJECTION[\"Mercator_1SP\"],";
    ogcwkt_osm += "PARAMETER[\"central_meridian\",0],PARAMETER[\"false_easting\",0], PARAMETER[\"false_northing\",0], UNIT[\"Meter\",1]]";
    unique_ptr<OGRSpatialReference> cs_osm = csManager->getCSbyRef(ogcwkt_osm);
    cs_osm->SetGeogCS("OSM", nullptr, nullptr, 0.0, 0.0);
    csManager->cooSysMapper->cooSysMap->insert(pair<string, shared_ptr<OGRSpatialReference>>("OSM", shared_ptr<OGRSpatialReference>(new OGRSpatialReference(*cs_osm))));

    //*/ -------------------------------------------------
    this->csManager->setReferences(cs_wgs84.get(), cs_pm.get(), cs_pm.get());
}
