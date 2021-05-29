#include <Data/ObjectData/tripdata.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <OpenGL/multipointsdisplayer.h>
#include <OpenGL/linedisplayer.h>
#include <ogr_geometry.h>
#include <Common/color.h>

using namespace std;


/**
 * \brief 	Default constructor of class tripData
 *
 * \param 	None
 * \return 	None
 */
tripData::tripData(Trip *trip): Data("tripData") {
   //this->trip = new Trip();
    this->trip = trip;


}

/**
 * \brief 	Default destructor of class tripData
 *
 * \param 	None
 * \return 	None
 */
tripData::~tripData() {

}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	None
 * \return 	None
 */
void tripData::draw() {

    std::unique_ptr<OGRMultiPoint> points = std::make_unique<OGRMultiPoint>();//point origin + point destination
    std::unique_ptr<OGRLinearRing> line = std::make_unique<OGRLinearRing>();//lin entre origin and destination


    double tempX = (trip->zoneOrigin->zone->getX());
    double tempY = (trip->zoneOrigin->zone->getX());

    std::unique_ptr<OGRPoint> point_origin = std::make_unique<OGRPoint>(tempX, tempY, 0.0);
    line->addPoint(tempX, tempY, 0.0);//Add point origin

    points->addGeometry(point_origin.get());


    tempX = (trip->zoneDestination->zone->getX());
    tempY = (trip->zoneDestination->zone->getX());


    std::unique_ptr<OGRPoint> point_destination = std::make_unique<OGRPoint>(tempX, tempY, 0.0);

    line->addPoint(tempX, tempY, 0.0);//Add point destination

    points->addGeometry(point_destination.get());


    Color c(1.0,1.0,1.0,0.7);

    MultipointsDisplayer::drawDirectly(points.get(), &c, 8);//Draw point destination and point origin


    LineDisplayer::drawLineArrow(line.get(), &c, 2, 20);
    //LineDisplayer::drawDirectly(line.get(), &c, 2);//Draw line entre two points

}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	t   a time_t
 * \return 	None
 *
 */
void tripData::draw(unsigned long long t) {

    this->draw();


    std::unique_ptr<OGRMultiPoint> points = std::make_unique<OGRMultiPoint>();



    std::unique_ptr<OGRPoint> point_current = this->trip->display(t);//get the current point

    //std::unique_ptr<OGRPoint> point_current = std::make_unique<OGRPoint>(t, t, 0.0);

    if(point_current != nullptr ) {

        points->addGeometry(point_current.get());//add the current point

    }

    Color c(1.0,0.0,0.0,1.0);


    MultipointsDisplayer::drawDirectly(points.get(), &c, 8);

    points->empty();



}
