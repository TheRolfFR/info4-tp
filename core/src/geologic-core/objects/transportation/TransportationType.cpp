/**
 * \file	TransportationType.cpp
 * \class	TransportationType
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of TransportationType object
 *
 * \details Methods of TransportationType object
 * A TransportationType object represents a mean of transport. A mean of transport is subject to hierarchy setup
 */

#include "geologic-core/objects/transportation/TransportationType.h"


/**
 * \brief 	Default constructor of class TransportationType
 *
 * \param 	None
 * \return 	None
 *
 * The typeId and typeDescription are set to "", the average speed to -1
 * The parents types and sub types are cleared
 */
TransportationType::TransportationType() {
    this->typeId = "";
    this->typeDescription = "";
    this->averageSpeed = -1;

    this->parents.clear();
    this->subMeans.clear();
}

/**
 * \brief 	Default destructor of class TransportationType
 *
 * \param 	None
 * \return 	None
 */
TransportationType::~TransportationType() {
    this->typeId = "";
    this->typeDescription = "";
    this->averageSpeed = -1;

    this->parents.clear();
    this->subMeans.clear();
}

/**
 * \brief 	Copy constructor of class TransportationType
 *
 * \param 	transportationType  The address of the TransportationType to copy
 * \return 	None
 */
TransportationType::TransportationType(TransportationType* transportationType) {
    this->typeId = transportationType->typeId;
    this->typeDescription = transportationType->typeDescription;
    this->averageSpeed = transportationType->averageSpeed;

    for (unsigned int i=0; i<transportationType->parents.size(); i++) this->parents.push_back(transportationType->parents[i]);
    for (unsigned int i=0; i<transportationType->subMeans.size(); i++) this->subMeans.push_back(transportationType->subMeans[i]);
}

/**
 * \brief 	Constructor with parameters of class TransportationType
 *
 * \param   typeId          The Id of the TransportationType
 * \param 	typeDescription The description of this TransportationType
 * \return 	None
 */
TransportationType::TransportationType(std::string typeId, std::string typeDescription) {
    this->typeId = typeId;
    this->typeDescription = typeDescription;
    this->averageSpeed = -1;

    this->parents.clear();
    this->subMeans.clear();
}
