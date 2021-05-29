/**
 * \file	ClusterKmeans.cpp
 * \class	ClusterKmeans
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of ClusterKmeans object
 *
 */

#include "geologic-core/algorithms/clustering/kmeans/ClusterKmeans.h"
#include "geologic-core/algorithms/clustering/kmeans/Kmeans.h"

using namespace std;
using namespace customToolbox;
using namespace geoMetrics;


/**
 * \brief 	Default constructor of class ClusterKmeans
 *
 * \param 	name    The name of the cluster
 * \return 	None
 *
 * Centroid and timestamp are set to nullptr
 */
ClusterKmeans::ClusterKmeans(string id, Kmeans* parent) : GeologicCluster(id, parent) {
    this->percStill = parent->percStill;
    this->diagDist = geoMetrics::distanceTo(env->getBbox().getBL().get(), env->getBbox().getTR().get(), env->getDataRef());
    this->generateRandomCentroid();
}

/**
 * \brief 	Default destructor of class ClusterKmeans
 *
 * \param 	name    The name of the cluster
 * \return 	None
 *
 * Centroid and timestamp are set to nullptr
 */
ClusterKmeans::~ClusterKmeans() {}

/**
 * \brief 	Default constructor of class ClusterKmeans
 *
 * \param 	name    The name of the cluster
 * \return 	None
 *
 * Centroid and timestamp are set to nullptr
 */
void ClusterKmeans::generateRandomCentroid() {
    setX(env->getBbox().minx + (rand()%((int) (env->getBbox().maxx - env->getBbox().minx))));
    setY(env->getBbox().miny + (rand()%((int) (env->getBbox().maxy - env->getBbox().miny))));
}

/**
 * \brief 	Default constructor of class ClusterKmeans
 *
 * \param 	name    The name of the cluster
 * \return 	None
 *
 * Centroid and timestamp are set to nullptr
 */
bool ClusterKmeans::computeCentroid() {

    if (this->records.size() <= 0) {
        this->generateRandomCentroid();
        return false;
    }

    OGRPoint lastCentroid(getX(), getY(), getZ());
    double newX = 0;
    double newY = 0;
    for (unsigned int i=0; i<this->records.size(); i++) {
        newX = ((newX*i) + this->records[i]->getX())/(i+1.0);
        newY = ((newY*i) + this->records[i]->getY())/(i+1.0);
    }
    setX(newX);
    setY(newY);

    double distance = geoMetrics::distanceTo(this, &lastCentroid, env->getDataRef());
    if (distance < (this->percStill*diagDist)) return true;
    return false;
}

/**
 * \brief 	Default constructor of class ClusterKmeans
 *
 * \param 	name    The name of the cluster
 * \return 	None
 *
 * Centroid and timestamp are set to nullptr
 */
void ClusterKmeans::clearRecords() {
    if (this->records.size() > 0) {
        this->records.clear();
    } else {
        this->generateRandomCentroid();
    }
}




