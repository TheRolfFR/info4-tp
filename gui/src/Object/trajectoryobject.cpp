/**
 * \file	TrajectoryObject.cpp
 * \class	VehiclePosition
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/01/2018
 * \brief	TrajectoryObject is a class representing a TrajectoryObject
 */

#include <Object/trajectoryobject.h>

#include <ResourceManagement/datamanager.h>


using namespace std;


/**
 * \brief 	Default constructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
TrajectoryObject::TrajectoryObject(Trajectory* trajectory) : Object("Trajectory Object") {
    this->trajectory = trajectory;

    m_data = DataManager::getInstance()->get("Empty");
}

/**
 * \brief 	Default destructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
TrajectoryObject::~TrajectoryObject() {}

/**
 * \brief 	Inherited method from class Object
 *
 * \param 	None
 * \return 	None
 */
//void TrajectoryObject::draw() {}

/**
 * \brief 	Inherited method from class Object
 *
 * \param 	t   a time_t
 * \return 	None
 * Display a vehicle as a disc at the current position
 */
/*void TrajectoryObject::draw(unsigned long long t) {

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
