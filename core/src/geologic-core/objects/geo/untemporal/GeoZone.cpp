/**
 * \file	GeoZone.cpp
 * \class	GeoZone
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of GeoZone object
 *
 * \details Methods of GeoZone object
 * A GeoZone represent any surface on the ground or in the air. It can describe buildings, zones, or radio cells.
 * A GeoZone inherits from OGRMultiPolygon
 */

#include "geologic-core/objects/geo/untemporal/GeoZone.h"
#include "geologic-core/utils/customToolbox.h"

using namespace std;
using namespace customToolbox;


/**
 * \brief 	Default constructor of class GeoZone
 *
 * \param 	None
 * \return 	None
 *
 */
GeoZone::GeoZone() {
    this->name = "";
    this->mainZone = nullptr;
    this->area = 0.0;
}

/**
 * \brief 	Default destructor of class GeoZone
 *
 * \param 	None
 * \return 	None
 */
GeoZone::~GeoZone() {
}

/**
 * \brief 	Constructor with parameters of class GeoZone
 *
 * \param 	name    The name of this GeoZone
 * \param   tags    A map of strings representing the main characteristics of this GeoZone
 * \return 	None
 *
 */
GeoZone::GeoZone(std::string name, std::unordered_map<std::string, std::string>* tags) {
    this->name = name;

    std::unordered_map<std::string, std::string>::iterator it = tags->begin();
    for (; it!=tags->end(); it++) {
        this->listTags.insert(std::pair<std::string, std::string>(it->first, it->second));
    }

    this->mainZone = nullptr;
    this->area = 0.0;
}

/**
 * \brief 	Copy constructor of class GeoZone
 *
 * \param 	zone    The GeoZone to copy
 * \return 	None
 *
 * The main component of the parent OGRMultiPolygon are copied too
 */
GeoZone::GeoZone(GeoZone* zone) : OGRMultiPolygon((OGRMultiPolygon) *zone) {
    OGRPoint tmp;
    zone->mainZone->Centroid(&tmp);
    std::unordered_map<std::string, std::string>::iterator ittags = zone->listTags.begin();
    for (; ittags!=zone->listTags.end(); ittags++) {
        this->listTags.insert(std::pair<std::string, std::string>(ittags->first, ittags->second));
    }

    this->name = zone->name;
    this->mainZone = nullptr;
    this->area = 0.0;
    this->detectMainZone();
    this->setBbox();
}

/**
 * \brief 	Returns display information to the caller
 *
 * \param 	timestamp   The current display time
 * \return 	true if the GeoZone has to be displayed, false otherwise
 */
bool GeoZone::display(double timestamp __attribute__((unused))) {
    return true;
}

/**
 * \brief 	Returns display information to the caller
 *
 * \param 	timestampOrigin         The starting display time
 * \param   timestampDestination    The ending display time
 * \return 	true if the GeoZone has to be displayed, false otherwise
 */
bool GeoZone::display(double timestampOrigin __attribute__((unused)), double timestampDestination __attribute__((unused))) {
    return true;
}

/**
 * \brief 	Sets the main zone of the GeoZone
 *
 * \param 	geomId  The id of the main zone of the GeoZone
 * \return 	None
 */
void GeoZone::setMainZone(int geomId) {
    if (geomId >= this->getNumGeometries()) return;
    OGRPolygon* geom = (OGRPolygon*) this->getGeometryRef(geomId);
    this->mainZone = geom;
    this->area = geom->get_Area();
    geom->Centroid((OGRPoint*) this);
}

/**
 * \brief 	Sets the Bbox values of this GeoZone
 *
 * \param 	None
 * \return 	None
 */
void GeoZone::setBbox() {
    if (this->mainZone == nullptr) return;

    OGRPoint currentPoint;
    this->mainZone->getExteriorRing()->getPoint(0, &currentPoint);
    double minx = currentPoint.getX();
    double miny = currentPoint.getY();
    double maxx = currentPoint.getX();
    double maxy = currentPoint.getY();
    for (unsigned int i=0; i<this->getNumPoints(); i++) {
        this->mainZone->getExteriorRing()->getPoint(i, &currentPoint);
        if (currentPoint.getX() < minx) minx = currentPoint.getX();
        if (currentPoint.getY() < miny) miny = currentPoint.getY();
        if (currentPoint.getX() > maxx) maxx = currentPoint.getX();
        if (currentPoint.getY() > maxy) maxy = currentPoint.getY();
    }

    bbox.set(minx, maxx, miny, maxy);
}

/**
 * \brief 	Automatically detects the main zone of this GeoZone based on the largest area
 *
 * \param 	None
 * \return 	None
 */
void GeoZone::detectMainZone() {
    int nbGeoms = this->getNumGeometries();
    double maxArea = 0.0;
    for (int geomId=0; geomId<nbGeoms; geomId++) {
        OGRPolygon* geom = (OGRPolygon*) this->getGeometryRef(geomId);

        OGRPoint tmp;
        geom->Centroid(&tmp);
        if (geom->get_Area() >= maxArea) {
            maxArea = geom->get_Area();
            this->setMainZone(geomId);
        }
    }
}

/**
 * \brief 	Returns the number of points used to describe this GeoZone (only the main zone)
 *
 * \param 	None
 * \return 	the number of points used to make the exterior ring of this GeoZone
 */
unsigned int GeoZone::getNumPoints() {
   if (this->mainZone == nullptr) return 0;
   return (unsigned int) this->mainZone->getExteriorRing()->getNumPoints();
}

/**
 * \brief 	Returns the OGRPoint at the desired id
 *
 * \param 	pointId The Id of the point to get back
 * \return 	The address of an OGRPoint
 */
shared_ptr<OGRPoint> GeoZone::getPoint(unsigned int pointId) {
   /*/
    OGRPoint* tmp = new OGRPoint;
    this->mainZone->getExteriorRing()->getPoint(pointId, tmp);
    shared_ptr<OGRPoint> returnPoint(tmp);
    delete(tmp);
    tmp = nullptr;
    return returnPoint;
    //*/

    shared_ptr<OGRPoint> returnPoint = make_shared<OGRPoint>();
    this->mainZone->getExteriorRing()->getPoint(pointId, returnPoint.get());
    return returnPoint;
}

/**
 * \brief 	Checks if an OGRPoint is included in the GeoZone (main zone)
 *
 * \param 	point   The OGRPoint to check
 * \return 	true if the OGRPoint is included in the main zone of the GeoZone
 */
bool GeoZone::containsPoint(OGRPoint* point) {
    if (this->bbox.isPointInRing(point))
        return this->mainZone->getExteriorRing()->isPointInRing(point);
    return false;
   //return this->Contains(point);
   //return point->Within(this);
}


