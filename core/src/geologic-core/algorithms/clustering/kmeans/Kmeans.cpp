/**
 * \file	Kmeans.cpp
 * \class   Kmeans
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/05/2015
 * \brief	Methods of Kmeans object
 *
 * Methods of Kmeans object
 */

#include "geologic-core/algorithms/clustering/kmeans/Kmeans.h"

using namespace std;
using namespace customToolbox;
using namespace std::chrono;


/**
 * \brief 	Default constructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
Kmeans::Kmeans() {
    this->numberK = 1;
    this->percStill = 0.01;
    srand(time(nullptr));
}

/**
 * \brief 	Default destructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
Kmeans::~Kmeans() {
    this->clusters_kmeans.clear();
}

/**
 * \brief 	Default constructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
void Kmeans::startKmeans(std::vector<GeographicalObject*>* population, unsigned int numberK) {
    //*/ -------------------------------------------------
    this->clearCluster();
    this->clusters_kmeans.clear();


    //*/ -------------------------------------------------
    this->numberK = numberK;
    this->population.clear();
    this->bbox.clear();

    if (population != nullptr) {
        for (unsigned int i=0; i<population->size(); i++) {
            bbox.update(population->at(i));
            this->population.push_back(population->at(i));
        }
    }

    //creation and intialization of the clusters
    for (unsigned int i=0; i<numberK; i++) {
        ClusterKmeans* ckm = new ClusterKmeans("cluster::"+str(i), this);
        clusters_kmeans.insert(pair<string, ClusterKmeans*>(ckm->id, ckm));
    }
    if (numberK <= 0) return;

    //*/ -------------------------------------------------
    bool allClustersStill = false;
    unsigned int watchdog = 100;
    unsigned int currentDog = 0;
    //cout << "Running Kmeans..." << endl;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (++currentDog < watchdog && !allClustersStill) {
        allClustersStill = true;

        //*/ -------------------------------------------------
        for (unsigned int i=0; i<this->clusters_kmeans.size(); i++) {
            this->clusters_kmeans["cluster::"+str(i)]->clearRecords();
        }

        //*/ -------------------------------------------------
        for (unsigned int i=0; i<this->population.size(); i++) {
            ClusterKmeans* ckm = this->findClosestCluster(this->population[i]);
            ckm->addObject(this->population[i]);
        }

        //*/ -------------------------------------------------
        for (unsigned int i=0; i<this->clusters_kmeans.size(); i++) {
            bool isStill = this->clusters_kmeans["cluster::"+str(i)]->computeCentroid();
            allClustersStill *= isStill;
        }
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double, std::milli> time_span = t2 - t1;
    //cout << "Kmeans done. " << "It took me " << time_span.count() << " milliseconds." << endl;
}

/**
 * \brief 	Default constructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
ClusterKmeans* Kmeans::findClosestCluster(GeographicalObject* object) {
    double bestDistance = -1;
    ClusterKmeans* bestCKm = nullptr;
    for (unsigned int i=0; i<clusters_kmeans.size(); i++) {
        ClusterKmeans* ckm = clusters_kmeans["cluster::"+str(i)];
        double distance = geoMetrics::distanceTo(ckm, object, dataRef);
        if (bestDistance == -1 || distance <= bestDistance) {
            bestDistance = distance;
            bestCKm = ckm;
        }
    }
    return bestCKm;
}

/**
 * \brief 	Default constructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
const std::unordered_map<string, GeologicCluster*>& Kmeans::getClusters() {
    this->clusters.clear();
    for (unsigned int i=0; i<clusters_kmeans.size(); i++) {
        ClusterKmeans* ckm = clusters_kmeans["cluster::"+str(i)];
        clusters.insert(pair<string, GeologicCluster*>("cluster::"+str(i), std::move((GeologicCluster*) ckm)));
    }
    return clusters;
}

