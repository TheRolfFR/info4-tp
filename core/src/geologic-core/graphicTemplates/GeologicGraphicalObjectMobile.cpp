/**
 * \file	GeologicGraphicalObjectMobile.cpp
 * \class   GeologicGraphicalObjectMobile
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of GeologicGraphicalObjectMobile object
 *
 * \details This class allows any object to inherit GeologicGraphicalObject as a Mobile object
 * This includes the obligation to define different display methods
 */

#include "geologic-core/graphicTemplates/GeologicGraphicalObjectMobile.h"
#include "geologic-core/objects/dynamic/Trajectory.h"
#include "geologic-core/algorithms/trajectories/Bspline.h"
#include "geologic-core/utils/customToolbox.h"

using namespace std;
using namespace customToolbox;


/**
 * \brief 	Default constructor of class GeologicGraphicalObjectMobile
 *
 * \param 	None
 * \return 	None
 */
GeologicGraphicalObjectMobile::GeologicGraphicalObjectMobile() {
    this->setType();
    this->bsplineModule = make_unique<Bspline>();
}

/**
 * \brief 	Default destructor of class GeologicGraphicalObjectMobile
 *
 * \param 	None
 * \return 	None
 */
GeologicGraphicalObjectMobile::~GeologicGraphicalObjectMobile() {}

/**
 * \brief 	Sets the graphical type. Inherited from GeologicGraphicalObject
 *
 * \param 	None
 * \return 	None
 */
void GeologicGraphicalObjectMobile::setType() {
    this->type = "Mobile";
}
