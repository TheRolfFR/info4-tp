/**
 * \file	TrajectoryData.cpp
 * \class	VehiclePosition
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/01/2018
 * \brief	TrajectoryData is a class representing a TrajectoryData
 */

#include <Data/trajectorydata.h>

using namespace std;


/**
 * \brief 	Default constructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
TrajectoryData::TrajectoryData() : Data("Trajectory Data") {
    std::vector<float> vertices = {0,0,0};

    setVertices(vertices);
    setStructureType(GL_POINTS);
}

/**
 * \brief 	Default destructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
TrajectoryData::~TrajectoryData() {}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	None
 * \return 	None
 */
//void TrajectoryData::draw() {}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	t   a time_t
 * \return 	None
 * Display a vehicle as a disc at the current position
 */
/*void TrajectoryData::draw(unsigned long long t) {

    //start
    glColor4d(0, 1, 0, 0.4); //green
    glPointSize(20.0);
    glBegin(GL_POINTS);
    glVertex3d(trajectory->trajectory->front()->getX(), trajectory->trajectory->front()->getY(), 0.0);
    glEnd();

    glLineWidth(10);
    glColor4d(1, 1, 1, 0.6); //09
    glBegin(GL_LINE_STRIP);
    for (unsigned int i=0; i<trajectory ->trajectory->size(); i++) {
        TemporalGeoPoint* currentPt = trajectory->trajectory->at(i);
        glVertex3d(currentPt->getX(), currentPt->getY(), 0.0);
    }
    glEnd();

    //end
    glColor4d(1, 0, 0, 0.4); //red
    glPointSize(20.0);
    glBegin(GL_POINTS);
    glVertex3d(trajectory->trajectory->back()->getX(), trajectory->trajectory->back()->getY(), 0.0);
    glEnd();

    //current
    std::unique_ptr<TemporalGeoPoint> currentPos = trajectory->getNewPositionAt(t);
    if (currentPos.get() == nullptr) currentPos.reset(trajectory->getClosestPoint(t).get());
    glColor4d(1, 1, 0, 0.4); //gold
    glPointSize(20.0);
    glBegin(GL_POINTS);
    glVertex3d(currentPos->getX(), currentPos->getY(), 0.0);
    glEnd();
}*/
