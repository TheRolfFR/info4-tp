/**
 * \file	CoordinateSystemManager.cpp
 * \class	CoordinateSystemManager
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Manages the different OGRSpatialReference objects of the library
 *
 * \details This class manages three OGRSpatialReference objects defined and used by the GUI.
 * These OGRSpatialReference are respectively dataRef, viewRef, displayRef
 * dataRef is for data representation (WGS-84)
 * viewRef is the OGRSpatialReference used in small display
 * displayRef is the OGRSpatialReference used in the main display
 */

#include "geologic-core/core/geologic-launcher/CoordinateSystemManager.h"
#include "geologic-core/utils/customToolbox.h"
#include "geologic-core/core/geologic-mapper/GeologicMapper.h"

using namespace std;
using namespace customToolbox;


CoordinateSystemManager* CoordinateSystemManager::instance = 0;

/**
 * \brief 	Default constructor of class CoordinateSystemManager
 *
 * \param 	None
 * \return 	None
 *
 * The CoordinateSystemManager is set to nullptr
 */
CoordinateSystemManager::CoordinateSystemManager() {
    cooSysMapper = std::make_unique<CoordinateSystemMap>();
    cooTraMapper = std::make_unique<CoordinateTransformationMap>();
    geod = std::make_unique<GeographicLib::Geodesic>(GeographicLib::Constants::WGS84_a(), GeographicLib::Constants::WGS84_f());
}

/**
 * \brief 	Returns the instance of the CoordinateSystemManager singleton
 *
 * \param 	None
 * \return 	None
 */
CoordinateSystemManager* CoordinateSystemManager::getInstance() {
    if (!instance) {
        instance = new CoordinateSystemManager;
    }
    return instance;
}

/**
 * \brief 	Returns the dataRef reference
 *
 * \param 	None
 * \return 	dataRef reference
 */
OGRSpatialReference* CoordinateSystemManager::getDataRef() {
    return this->dataRef.get();
}

/**
 * \brief 	Returns the viewRef reference
 *
 * \param 	None
 * \return 	viewRef reference
 */
OGRSpatialReference* CoordinateSystemManager::getViewRef() {
    return this->viewRef.get();
}

/**
 * \brief 	Returns the displayRef reference
 *
 * \param 	None
 * \return 	displayRef reference
 */
OGRSpatialReference* CoordinateSystemManager::getDisplayRef() {
    return this->displayRef.get();
}

/**
 * \brief 	Sets the main OGRSpatialReference of the library
 *
 * \param 	dataRef     The data OGRSpatialReference
 * \param 	viewRef     The view OGRSpatialReference
 * \param 	displayRef  The display OGRSpatialReference
 * \return 	None
 */
void CoordinateSystemManager::setReferences(OGRSpatialReference* dataRef, OGRSpatialReference* viewRef, OGRSpatialReference* displayRef) {
    this->setDataRef(dataRef);
    this->setViewRef(viewRef);
    this->setDisplayRef(displayRef);
}

/**
 * \brief 	Sets the dataRef OGRSpatialReference of the library
 *
 * \param 	dataRef The data OGRSpatialReference
 * \return 	None
 */
void CoordinateSystemManager::setDataRef(OGRSpatialReference* dataRef) {
    this->dataRef.reset(); // Don't take ownership of *dataref
    this->dataRef = unique_ptr<OGRSpatialReference>(new OGRSpatialReference(*dataRef)); // Better create a new spatialref
}

/**
 * \brief 	Sets the viewRef OGRSpatialReference of the library
 *
 * \param 	viewRef The view OGRSpatialReference
 * \return 	None
 */
void CoordinateSystemManager::setViewRef(OGRSpatialReference* viewRef) {
    this->viewRef.reset();
    this->viewRef = unique_ptr<OGRSpatialReference>(new OGRSpatialReference(*viewRef));
}

/**
 * \brief 	Sets the displayRef OGRSpatialReference of the library
 *
 * \param 	displayRef  The display OGRSpatialReference
 * \return 	None
 */
void CoordinateSystemManager::setDisplayRef(OGRSpatialReference* displayRef) {
    this->displayRef.reset();
    this->displayRef = unique_ptr<OGRSpatialReference>(new OGRSpatialReference(*displayRef));
}

/**
 * \brief 	Searches the OGRSpatialReference using OGRSpatialReference
 *
 * \param 	None
 * \return 	None
 */
OGRSpatialReference* CoordinateSystemManager::getCSbyName(string csName) {
    OGRSpatialReference* csr = nullptr;
    unordered_map<string, std::shared_ptr<OGRSpatialReference>>::iterator it = this->cooSysMapper->cooSysMap->begin();
    for (; it!=cooSysMapper->cooSysMap->end(); it++) {
        if (it->first == csName) {
            csr = it->second.get();
            break;
        }
    }
    if (csr == nullptr) {
        cout << "CoordinateSystemManager::Error, the required Coordinate System is not referenced in my maps" << endl;
    }
    return csr;
}

/**
 * \brief 	Searches the OGRSpatialReference using OGRSpatialReference
 *
 * \param 	None
 * \return 	None
 */
unique_ptr<OGRSpatialReference> CoordinateSystemManager::getCSbyRef(string refCode) {
    unique_ptr<OGRSpatialReference> csr = make_unique<OGRSpatialReference>();
    csr->SetFromUserInput(refCode.c_str());
    if (csr.get() == nullptr) {
        cout << "CoordinateSystemManager::Error, the required Coordinate System is not referenced by this refCode" << endl;
    }
    return csr;
}

/**
 * \brief 	Returns the name of the OGRSpatialReference (GEOGCS)
 *
 * \param 	Name
 * \return 	None
 */
std::string CoordinateSystemManager::getCSName(OGRSpatialReference* csr) {
    return csr->GetAttrValue("GEOGCS"); // PROJCS ?
}
