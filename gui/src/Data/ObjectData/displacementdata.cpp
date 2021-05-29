#include <Data/ObjectData/displacementdata.h>
#include <OpenGL/multipointsdisplayer.h>
#include <OpenGL/linedisplayer.h>
#include <ogr_geometry.h>
#include <Common/color.h>

/**
 * \brief 	Default constructor of class DisplacementData
 *
 * \param 	None
 * \return 	None
 */
DisplacementData::DisplacementData(Displacement *displacment) : Data("DisplacementData") {
    this->displacment = displacment;

}

/**
 * \brief 	Default destructor of class DisplacementData
 *
 * \param 	None
 * \return 	None
 */
DisplacementData::~DisplacementData() {

}
/**
 * \brief 	Inherited method from class Data
 *
 * \param 	None
 * \return 	None
 */
void DisplacementData::draw() {

    std::unique_ptr<OGRLinearRing> line = std::make_unique<OGRLinearRing>();//line

    TemporalGeoZone* p0 = this->displacment->zoneOrigin;

    TemporalGeoZone* p1 = this->displacment->zoneDestination;

    unsigned long long t= p0->timestamp;

    while ((t >= p0->timestamp) && (t <= p1->timestamp)) {

        std::unique_ptr<OGRPoint> tempPoint;

        tempPoint = this->displacment->display(t,0.75);

        if(tempPoint != nullptr) {

            line->addPoint(tempPoint->getX(),tempPoint->getY(),tempPoint->getZ());
        }

        t++;
    }
    Color c(1.0,1.0,1.0,0.7);

    int taille = this->displacment->trips.size() % 10 ;

    LineDisplayer::drawDirectly(line.get(), &c, taille);


}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	t   a time_t
 * \return 	None
 *
 */
void DisplacementData::draw(unsigned long long t) {
    this->draw();

}

