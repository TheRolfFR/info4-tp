/**
 * \file	ClusteringEnvironment.cpp
 * \class	ClusteringEnvironment
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 */

#include "geologic-core/algorithms/clustering/ClusteringEnvironment.h"

using namespace std;

/**
 * \brief 	Default constructor of class GeologicEnvironment
 *
 * \param 	None
 * \return 	None
 */
ClusteringEnvironment::ClusteringEnvironment() {
    this->dataRef = CoordinateSystemManager::getInstance()->getDataRef();
}

/**
 * \brief 	Default constructor of class GeologicEnvironment
 *
 * \param 	None
 * \return 	None
 */
void ClusteringEnvironment::setDataRef(OGRSpatialReference* dataRef) {
    this->dataRef = dataRef;
}

/**
 * \brief 	Default constructor of class GeologicEnvironment
 *
 * \param 	None
 * \return 	None
 */
ClusteringEnvironment::~ClusteringEnvironment() {
    this->clearCluster();
    this->population.clear();
}

/**
 * \brief 	Default constructor of class GeologicEnvironment
 *
 * \param 	None
 * \return 	None
 */
void ClusteringEnvironment::clearCluster() {
    unordered_map<string, GeologicCluster*>::iterator it = this->clusters.begin();
    while (it != this->clusters.end()) {
        if (it->second != nullptr) delete(it->second);
        it->second = nullptr;
        it++;
    }
    this->clusters.clear();
}

/**
 * \brief 	Default constructor of class GeologicEnvironment
 *
 * \param 	None
 * \return 	None
 */
Bbox& ClusteringEnvironment::getBbox() {
    return bbox;
}

/**
 * \brief 	Default constructor of class GeologicEnvironment
 *
 * \param 	None
 * \return 	None
 */
OGRSpatialReference* ClusteringEnvironment::getDataRef() {
    return dataRef;
}

/**
 * \brief 	Default constructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
const std::unordered_map<string, GeologicCluster*>& ClusteringEnvironment::getClusters() {
    unordered_map<string, GeologicCluster*>::iterator it = this->clusters.begin();
    while (it != this->clusters.end()) {
        it->second->computeCentroid();
        it++;
    }
    return clusters;
}
