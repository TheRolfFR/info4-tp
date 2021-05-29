/**
 * \file	GeologicModule.cpp
 * \class	GeologicModule
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	The main file of the library
 *
 *  \details This class is acting as a proxy that links to GeologicLauncher (which contains references to the GeologicMapper, and CoordinateSystemManager)
 * This class is based on the Module role, which means it can be added as a module for any other project.
 * This declare that project as a Module object. The project can subscribe to different roles, and the Module object has to return the different roles subscribed to.
 */

#include "geologic-core/core/GeologicModule.h"


GeologicModule* GeologicModule::instance = 0;

/**
 * \brief 	Default constructor of class GeologicModule
 *
 * \param 	None
 * \return 	None
 */
GeologicModule::GeologicModule() {
    this->launcher = GeologicLauncher::getInstance();
}

/**
 * \brief 	Returns the instance of the GeologicModule singleton
 *
 * \param 	None
 * \return 	The reference of the GeologicModule singleton
 */
GeologicModule* GeologicModule::getInstance() {
    if (!instance) {
        instance = new GeologicModule;
    }
    return instance;
}

/**
 * \brief 	Returns the address of the GeologicLauncher object
 *
 * \param 	None
 * \return 	The address of the GeologicLauncher object
 */
GeologicLauncher* GeologicModule::getLauncher() {
    return GeologicModule::getInstance()->launcher;
}

/**
 * \brief 	Returns the roles held by the GeologicModule class, i.e, the role Module
 *
 * \param 	None
 * \return 	A vector of roles
 */
std::vector<std::string> GeologicModule::getSubscribedRoles() {
    std::vector<std::string> myRoles {RoleModule::getRoleName()};
    return myRoles;
}
