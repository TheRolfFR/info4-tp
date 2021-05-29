#include <Object/arrowobject.h>

#include <Common/utils2.h>

#include <ResourceManagement/datamanager.h>

using std::cout;
using std::endl;

/**
 * \brief 	Default constructor of class ArrowObject
 *
 * \param 	None
 * \return 	None
 */
ArrowObject::ArrowObject(): Object("ArrowObject")
{
    m_data = DataManager::getInstance()->get("point");
}


/**
 * \brief 	Default destructor of class ArrowObject
 *
 * \param 	None
 * \return 	None
 */
ArrowObject::~ArrowObject(){
}


/**
 * \brief 	Inherited method from class Object
 *
 * \param 	None
 * \return 	None
 */
void ArrowObject::draw(QMatrix4x4 &projection, QMatrix4x4 &view) {
/*    if (parent->trackedVehicle != nullptr) {
        Trajectory* currentTraj = trackedVehicle->listTrajectories["0"];
        trackedVehicle->color = Color(240/255.0, 147/255.0, 43/255.0);
*/
}


/**
 * \brief 	Inherited method from class Object
 *
 * \param 	t   a time_t
 * \return 	None
 *
 */
void ArrowObject::draw(QMatrix4x4 &projection, QMatrix4x4 &view, unsigned long long t) {
    this->draw(projection, view);
}
