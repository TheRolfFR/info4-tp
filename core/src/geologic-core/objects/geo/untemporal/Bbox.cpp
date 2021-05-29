/**
 * \file	Bbox.cpp
 * \class	Bbox
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Bbox object
 *
 * \details Methods of Bbox object
 */

#include "geologic-core/objects/geo/untemporal/Bbox.h"
#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"
#include <iostream>

using namespace std;


/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
Bbox::Bbox() {
    this->createOGRPoints();
}

/**
 * \brief 	Default destructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
Bbox::~Bbox() {}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
Bbox::Bbox(double minx, double maxx, double miny, double maxy): OGRLinearRing() {
    this->minx = minx;
    this->miny = miny;
    this->maxx = maxx;
    this->maxy = maxy;
    this->first = false;
    this->createOGRPoints();
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
Bbox::Bbox(Bbox& bbox): OGRLinearRing() {
    this->minx = bbox.minx;
    this->miny = bbox.miny;
    this->maxx = bbox.maxx;
    this->maxy = bbox.maxy;
    this->first = false;
    this->createOGRPoints();
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
void Bbox::createOGRPoints() {
    this->empty();
    this->addPoint(this->minx, this->miny, 0.0);
    this->addPoint(this->minx, this->maxy, 0.0);
    this->addPoint(this->maxx, this->maxy, 0.0);
    this->addPoint(this->maxx, this->miny, 0.0);
    if (!bool(this->get_IsClosed())) this->closeRings();

    width = this->maxx - this->minx;
    height = this->maxy - this->miny;
    diagonal = 0; //this->getBL()->Distance(this->getTR().get());
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
shared_ptr<OGRPoint> Bbox::getBL() {
    shared_ptr<OGRPoint> returnPoint = make_shared<OGRPoint>();
    this->getPoint(0, returnPoint.get());
    return returnPoint;
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
shared_ptr<OGRPoint> Bbox::getTL() {
    shared_ptr<OGRPoint> returnPoint = make_shared<OGRPoint>();
    this->getPoint(1, returnPoint.get());
    return returnPoint;
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
shared_ptr<OGRPoint> Bbox::getTR() {
    shared_ptr<OGRPoint> returnPoint = make_shared<OGRPoint>();
    this->getPoint(2, returnPoint.get());
    return returnPoint;
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
shared_ptr<OGRPoint> Bbox::getBR() {
    shared_ptr<OGRPoint> returnPoint = make_shared<OGRPoint>();
    this->getPoint(3, returnPoint.get());
    return returnPoint;
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
void Bbox::update(OGRPoint* point) {
    if (!isPointInRing(point)) {
        double ptX = point->getX();
        double ptY = point->getY();
        if (first) {
            this->maxx = ptX;
            this->minx = ptX;
            this->maxy = ptY;
            this->miny = ptY;
            first = false;
        } else {
            if (ptX > maxx) this->maxx = ptX;
            if (ptX < minx) this->minx = ptX;
            if (ptY > maxy) this->maxy = ptY;
            if (ptY < miny) this->miny = ptY;
        }
        this->createOGRPoints();
    }
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
void Bbox::update(const Bbox& bbox) {
    for (unsigned int i=0; i<4; i++) {
        OGRPoint point;
        bbox.getPoint(i, &point);
        this->update(&point);
    }
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
void Bbox::set(double minx, double maxx, double miny, double maxy) {
    this->minx = minx;
    this->miny = miny;
    this->maxx = maxx;
    this->maxy = maxy;
    this->createOGRPoints();
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
void Bbox::set(Bbox& bbox) {
    this->minx = bbox.minx;
    this->miny = bbox.miny;
    this->maxx = bbox.maxx;
    this->maxy = bbox.maxy;
    this->createOGRPoints();
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
Bbox& Bbox::operator =(const std::tuple<double, double, double, double>& bbox) {
    this->minx = std::get<0>(bbox);
    this->maxx = std::get<2>(bbox);
    this->miny = std::get<1>(bbox);
    this->maxy = std::get<3>(bbox);
    this->createOGRPoints();
    return (*this);
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
Bbox& Bbox::operator =(Bbox& bbox) {
    this->minx = bbox.minx;
    this->miny = bbox.miny;
    this->maxx = bbox.maxx;
    this->maxy = bbox.maxy;
    this->createOGRPoints();
    return (*this);
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
bool Bbox::operator !=(Bbox& bbox) {
    return (bbox.minx != minx && bbox.maxx != maxx && bbox.miny != miny && bbox.maxy != maxy);
}

/**
 * \brief 	Default constructor of class Bbox
 *
 * \param 	None
 * \return 	None
 */
void Bbox::clear() {
    this->first = true;
    this->set(0, 0, 0, 0);
}


/**
 * \brief wgs84Bbox computes the wgs84 bounding box from a center, a zoom and screen size.
 * \param p the center of the screen, in wgs84
 * \param w the screen width in pixels
 * \param h the screen height in pixels
 * \param zoom the zoom as defined in well known tile servers
 */
void Bbox::setWGS84Bbox(OGRPoint* point, int width, int height, const int zoom) {
    double center_x, center_y;
    double alpha = 1.0 / (256.0 * pow(2.0, zoom));

    tie(center_x, center_y) = geoMetrics::wgs84ToOsm(point);

    double view_x_min = center_x - width / 2.0 * alpha;
    double view_x_max = center_x + width / 2.0 * alpha;
    double view_y_min = 1.0 - (center_y + height / 2.0 * alpha);
    double view_y_max = 1.0 - (center_y - height / 2.0 * alpha);
    double wgs84_x_min, wgs84_x_max, wgs84_y_min, wgs84_y_max;

    tie(wgs84_x_min, wgs84_y_min) = geoMetrics::OsmToWgs84(view_x_min, 1.0 - view_y_min);
    tie(wgs84_x_max, wgs84_y_max) = geoMetrics::OsmToWgs84(view_x_max, 1.0 - view_y_max);

    this->minx = wgs84_x_min;
    this->maxx = wgs84_x_max;
    this->miny = wgs84_y_min;
    this->maxy = wgs84_y_max;
    this->createOGRPoints();
    //return make_tuple(wgs84_x_min, wgs84_y_min, wgs84_x_max, wgs84_y_max);
}

/**
 * \brief wgs84Bbox computes the wgs84 bounding box from a center, a zoom and screen size.
 * \param p the center of the screen, in wgs84
 * \param w the screen width in pixels
 * \param h the screen height in pixels
 * \param zoom the zoom as defined in well known tile servers
 */
ostream& operator <<(ostream& os, Bbox& me) {
    cout << "Bbox:: Xmin:" << me.minx << " Ymin:" << me.miny;
    cout << " Xmax:" << me.maxx << " Ymax:" << me.maxy << endl;
    return os;
}
