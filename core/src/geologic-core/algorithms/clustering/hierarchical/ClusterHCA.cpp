/**
 * \file	ClusterHCA.cpp
 * \class   ClusterHCA
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/05/2015
 * \brief	Methods of ClusterHCA object
 *
 * Methods of ClusterHCA object
 */

#include "geologic-core/algorithms/clustering/hierarchical/ClusterHCA.h"
#include "geologic-core/algorithms/clustering/hierarchical/Hierarchical.h"

using namespace std;
using namespace customToolbox;


/**
 * \brief 	Default constructor of class ClusterHCA
 *
 * \param 	None
 * \return 	None
 */
ClusterHCA::ClusterHCA(string id, Hierarchical* parent): GeologicCluster(id, parent) {}

/**
 * \brief 	Default destructor of class ClusterHCA
 *
 * \param 	None
 * \return 	None
 */
ClusterHCA::~ClusterHCA() {
    this->subClusters.clear();
}

/**
 * \brief 	Default destructor of class ClusterHCA
 *
 * \param 	None
 * \return 	None
 */
const std::vector<ClusterHCA*>& ClusterHCA::getSubClusters() {
    return this->subClusters;
}

/**
 * \brief 	Default destructor of class ClusterHCA
 *
 * \param 	None
 * \return 	None
 */
void ClusterHCA::addSubCluster(ClusterHCA* c) {
    this->subClusters.push_back(c);
}

/**
 * \brief 	Default constructor of class ClusterKmeans
 *
 * \param 	name    The name of the cluster
 * \return 	None
 *
 * Centroid and timestamp are set to nullptr
 */
bool ClusterHCA::computeCentroid() {
    double newX = 0;
    double newY = 0;
    vector<GeographicalObject*> tempVect = this->getHCARecords();

    for (unsigned int i=0; i<tempVect.size(); i++) {
        newX = ((newX*i) + tempVect[i]->getX())/(i+1.0);
        newY = ((newY*i) + tempVect[i]->getY())/(i+1.0);
    }
    setX(newX);
    setY(newY);
    return true;
}

/**
 * \brief 	Default constructor of class ClusterKmeans
 *
 * \param 	name    The name of the cluster
 * \return 	None
 *
 * Centroid and timestamp are set to nullptr
 */
vector<GeographicalObject*> ClusterHCA::getHCARecords() {
    vector<GeographicalObject*> tempVect;
    if (this->records.size() <= 0) {
        for (unsigned int i=0; i<this->subClusters.size(); i++) {
            ClusterHCA* subc = this->subClusters[i];
            vector<GeographicalObject*> newRecs = subc->getHCARecords();
            tempVect.insert(tempVect.end(), newRecs.begin(), newRecs.end());
        }
        return tempVect;
    } else {
        return records;
    }
}

/**
 * \brief 	Default constructor of class ClusterKmeans
 *
 * \param 	name    The name of the cluster
 * \return 	None
 *
 * Centroid and timestamp are set to nullptr
 */
void ClusterHCA::insertRecords() {
    if (this->subClusters.size() > 0) {
        this->records.clear();
    }
    vector<GeographicalObject*> newRecs = this->getHCARecords();
    this->records.insert(records.end(), newRecs.begin(), newRecs.end());
}
