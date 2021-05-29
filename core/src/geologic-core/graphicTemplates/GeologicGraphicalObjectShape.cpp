/**
 * \file	GeologicGraphicalObjectShape.cpp
 * \class   GeologicGraphicalObjectShape
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of GeologicGraphicalObjectShape object
 *
 * \details This class allows any object to inherit GeologicGraphicalObject as a Shape object
 * This includes the obligation to define two display methods
 */

#include "geologic-core/graphicTemplates/GeologicGraphicalObjectShape.h"
#include "geologic-core/utils/customToolbox.h"

using namespace std;
using namespace customToolbox;


/**
 * \brief 	Default constructor of class GeologicGraphicalObjectShape
 *
 * \param 	None
 * \return 	None
 */
GeologicGraphicalObjectShape::GeologicGraphicalObjectShape() {
    this->setType();
}

/**
 * \brief 	Default destructor of class GeologicGraphicalObjectShape
 *
 * \param 	None
 * \return 	None
 */
GeologicGraphicalObjectShape::~GeologicGraphicalObjectShape() {}

/**
 * \brief 	Sets the graphical type. Inherited from GeologicGraphicalObject
 *
 * \param 	None
 * \return 	None
 */
void GeologicGraphicalObjectShape::setType() {
    this->type = "Shape";
}
