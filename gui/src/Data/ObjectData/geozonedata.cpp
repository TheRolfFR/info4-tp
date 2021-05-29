#include <Data/ObjectData/geozonedata.h>
#include <OpenGL/quaddisplayer.h>

/**
 * \brief 	Default constructor of class GeoZoneData
 *
 * \param 	None
 * \return 	None
 */
GeoZoneData::GeoZoneData(GeoZone *geozone) : Data("GeoZoneData")
{
    this->geozone = geozone;
}

/**
 * \brief 	Default destructor of class GeoZoneData
 *
 * \param 	None
 * \return 	None
 */
GeoZoneData::~GeoZoneData() {

}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	None
 * \return 	None
 */
void GeoZoneData::draw(){
    //std::unique_ptr<BboxData> bbox = std::make_unique<BboxData>(this->geozone->bbox);
    //bbox->draw();

    OGRPoint* corner[4];

    std::shared_ptr<OGRPoint> pointBL = this->geozone->bbox.getBL();
    corner[0] = pointBL.get();

    std::shared_ptr<OGRPoint> pointBR = this->geozone->bbox.getBR();
    corner[1] = pointBR.get();

    std::shared_ptr<OGRPoint> pointTL = this->geozone->bbox.getTL();
    corner[3] = pointTL.get();

    std::shared_ptr<OGRPoint> pointTR = this->geozone->bbox.getTR();
    corner[2] = pointTR.get();


    QuadDisplayer::drawQuad(corner);

}


/**
 * \brief 	Inherited method from class Data
 *
 * \param 	t   a time_t
 * \return 	None
 *
 */
void GeoZoneData::draw(unsigned long long t) {
    this->draw();
}
