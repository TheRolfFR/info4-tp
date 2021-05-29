/**
 * \file	GeologicGraphicalObjectFlow.cpp
 * \class   GeologicGraphicalObjectFlow
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of GeologicGraphicalObjectFlow object
 *
 * \details This class allows any object to inherit GeologicGraphicalObject as a Flow object
 * This includes the obligation to define a display method
 */

#include "geologic-core/graphicTemplates/GeologicGraphicalObjectFlow.h"
#include "geologic-core/utils/customToolbox.h"

using namespace std;
using namespace customToolbox;


/**
 * \brief 	Default constructor of class GeologicGraphicalObjectFlow
 *
 * \param 	None
 * \return 	None
 */
GeologicGraphicalObjectFlow::GeologicGraphicalObjectFlow() {
    this->setType();
}

/**
 * \brief 	Default destructor of class GeologicGraphicalObjectFlow
 *
 * \param 	None
 * \return 	None
 */
GeologicGraphicalObjectFlow::~GeologicGraphicalObjectFlow() {}

/**
 * \brief 	Sets the graphical type. Inherited from GeologicGraphicalObject
 *
 * \param 	None
 * \return 	None
 */
void GeologicGraphicalObjectFlow::setType() {
    this->type = "Flow";
}
