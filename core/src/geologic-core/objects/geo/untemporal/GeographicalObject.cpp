/**
 * \file	GeographicalObject.cpp
 * \class	GeographicalObject
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of GeographicalObject object
 *
 * \details Methods of GeographicalObject object
 */

#include "geologic-core/objects/geo/untemporal/GeographicalObject.h"
#include "geologic-core/objects/geo/untemporal/GridMesh.h"

using namespace std;


/**
 * \brief 	Default constructor of class GeographicalObject
 *
 * \param 	None
 * \return 	None
 */
GeographicalObject::GeographicalObject() {
    this->name = "";
    this->setX(0);
    this->setY(0);
    this->setZ(0);
}

/**
 * \brief 	Default constructor of class GeographicalObject
 *
 * \param 	None
 * \return 	None
 */
GeographicalObject::GeographicalObject(double x, double y, double z) {
    this->name = "";
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

/**
 * \brief 	Default constructor of class GeographicalObject
 *
 * \param 	None
 * \return 	None
 */
GeographicalObject::GeographicalObject(string name, double x, double y, double z) {
    this->name = name;
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

/**
 * \brief 	Default constructor of class GeographicalObject
 *
 * \param 	None
 * \return 	None
 */
GeographicalObject::GeographicalObject(GeographicalObject* obj) {
    this->name = obj->name;
    this->setX(obj->getX());
    this->setY(obj->getY());
    this->setZ(obj->getZ());
}

/**
 * \brief 	Default constructor of class GeographicalObject
 *
 * \param 	None
 * \return 	None
 */
GeographicalObject::GeographicalObject(OGRPoint* pt) {
    this->name = "";
    this->setX(pt->getX());
    this->setY(pt->getY());
    this->setZ(pt->getZ());
}

/**
 * \brief 	Default constructor of class GeographicalObject
 *
 * \param 	None
 * \return 	None
 */
GeographicalObject::GeographicalObject(string name, OGRPoint* pt) {
    this->name = name;
    this->setX(pt->getX());
    this->setY(pt->getY());
    this->setZ(pt->getZ());
}

/**
 * \brief 	Default destructor of class GeographicalObject
 *
 * \param 	None
 * \return 	None
 */
GeographicalObject::~GeographicalObject() {}
