#include <Data/ObjectData/temporalgeopointdata.h>
#include <OpenGL/multipointsdisplayer.h>

/**
 * \brief 	Default constructor of class TemporalGeoPointData
 *
 * \param 	None
 * \return 	None
 */
TemporalGeoPointData::TemporalGeoPointData(TemporalGeoPoint *tpgPoint) : Data("TemporalGeoPointData")
{
    this->tpgPoint = tpgPoint;
    /*/this->tpgPoint = new TemporalGeoPoint();
    this->tpgPoint->setX(0.0);
    this->tpgPoint->setY(0.0);
    this->tpgPoint->setZ(0.0);/*/

}

/**
 * \brief 	Default destructor of class TemporalGeoPointData
 *
 * \param 	None
 * \return 	None
 */
TemporalGeoPointData::~TemporalGeoPointData() {

}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	None
 * \return 	None
 */
void TemporalGeoPointData::draw() {

}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	t   a time_t
 * \return 	None
 *
 */
void TemporalGeoPointData::draw(unsigned long long t) {

    std::unique_ptr<OGRMultiPoint> points = std::make_unique<OGRMultiPoint>();//point origin + point destination


    //std::unique_ptr<OGRPoint> point_origin = std::make_unique<OGRPoint>(-110, -70.0, 0.0);

    points->addGeometry(this->tpgPoint);


    //c = Color((rand()%100)/100.0, (rand()%100)/100.0, (rand()%100)/100.0, 1.0);

    Color c = Color(1.0,1.0,1.0,1.0);

    MultipointsDisplayer::drawDirectly(points.get(),&c, 20.0);

}
