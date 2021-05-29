#include <Data/ObjectData/bboxdata.h>
#include <OpenGL/quaddisplayer.h>

/**
 * \brief 	Default constructor of class BboxData
 *
 * \param 	None
 * \return 	None
 */
BboxData::BboxData(Bbox* bbox) : Data("BboxData")
{
    this->bbox = bbox;
}

/**
 * \brief 	Default destructor of class BboxData
 *
 * \param 	None
 * \return 	None
 */
BboxData::~BboxData() {

}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	None
 * \return 	None
 */
void BboxData::draw() {

    OGRPoint* corner[4];

    std::shared_ptr<OGRPoint> pointBL = bbox->getBL();
    corner[0] = pointBL.get();

    std::shared_ptr<OGRPoint> pointBR = bbox->getBR();
    corner[1] = pointBR.get();

    std::shared_ptr<OGRPoint> pointTL = bbox->getTL();
    corner[3] = pointTL.get();

    std::shared_ptr<OGRPoint> pointTR = bbox->getTR();
    corner[2] = pointTR.get();


    QuadDisplayer::drawQuad(corner);



}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	t   a time_t
 * \return 	None
 * Display a bbox
 */
void BboxData::draw(unsigned long long t) {
    this->draw();
}
