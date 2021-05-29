/**
 * \file	Hierarchical.cpp
 * \class   Hierarchical
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/05/2015
 * \brief	Methods of Hierarchical object
 *
 * Methods of Hierarchical object
 */

#include "geologic-core/algorithms/clustering/hierarchical/Hierarchical.h"

using namespace std;
using namespace customToolbox;
using namespace std::chrono;


/**
 * \brief 	Default constructor of class Hierarchical
 *
 * \param 	None
 * \return 	None
 */
Hierarchical::Hierarchical() {
    this->numberK = 3;
    this->addedClusters = 0;
    this->grid = nullptr;
    srand(time(nullptr));
}

/**
 * \brief 	Default destructor of class Hierarchical
 *
 * \param 	None
 * \return 	None
 */
Hierarchical::~Hierarchical() {
    this->clearCluster();
    if (this->grid != nullptr) delete(this->grid);
    this->grid = nullptr;

    this->clusters_hca.clear();
}

/**
 * \brief 	Default constructor of class Hierarchical
 *
 * \param 	None
 * \return 	None
 */
void Hierarchical::startHCA(std::vector<GeographicalObject*>* population, unsigned int numberK) {
    //*/ -------------------------------------------------
    this->clearCluster();

    //*/ -------------------------------------------------
    this->numberK= numberK;
    this->addedClusters = 0;
    this->population.clear();
    this->bbox.clear();

    if (population != nullptr) {
        if (numberK > population->size()) return;
        for (unsigned int i=0; i<population->size(); i++) {
            bbox.update(population->at(i));
            this->population.push_back(population->at(i));

            ClusterHCA* newCluster = new ClusterHCA("cluster::"+str(this->addedClusters++), this);
            newCluster->addObject(population->at(i));
            newCluster->computeCentroid();
            this->clusters_hca.insert(pair<string, ClusterHCA*>(newCluster->id, newCluster));
        }
    }

    double diagDist = geoMetrics::distanceTo(bbox.getBL().get(), bbox.getTR().get(), this->getDataRef());
    double min_pdm = 0.01*diagDist;
    double longDist = geoMetrics::distanceTo(bbox.getBL().get(), bbox.getBR().get(), this->getDataRef())+min_pdm;
    double heigDist = geoMetrics::distanceTo(bbox.getBL().get(), bbox.getTL().get(), this->getDataRef())+min_pdm;
    double envSize = std::max(longDist, heigDist);
    this->grid = new Grid(bbox.getBL().get(), envSize);
    // min_pdm = (envSize) / (2^(level))
    // => level = log(envSize / min_pdm) / log(2)

    this->grid->meshEnv(std::round(std::log10(envSize/min_pdm)/std::log10(2)));
    unordered_map<string, ClusterHCA*>::iterator it = this->clusters_hca.begin();
    for (; it!=this->clusters_hca.end(); it++) {
        ClusterHCA* chca = it->second;
        this->grid->update(chca, chca, 0);
    }

    //*/ -------------------------------------------------
    //cout << "Running HCA..." << endl;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (this->clusters_hca.size() > 1) {
        //find best pair
        double bestDistance = -1;
        pair<ClusterHCA*, ClusterHCA*> bestPair;
        it = this->clusters_hca.begin();
        for (; it!=this->clusters_hca.end(); it++) {
            ClusterHCA* chca = it->second;
            ClusterHCA* chcb = this->findClosestCluster(chca);
            double distance = geoMetrics::distanceTo(chca, chcb, dataRef);
            if (bestDistance == -1 || distance <= bestDistance) {
                bestDistance = distance;
                bestPair.first = chca;
                bestPair.second = chcb;
            }
        }
        //merge best pair
        this->mergeCluster(bestPair.first, bestPair.second);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double, std::milli> time_span = t2 - t1;
    //cout << "HCA done. " << "It took me " << time_span.count() << " milliseconds." << endl;

    if (this->grid != nullptr) delete(this->grid);
    this->grid = nullptr;
}

/**
 * \brief 	Default constructor of class Hierarchical
 *
 * \param 	None
 * \return 	None
 */
ClusterHCA* Hierarchical::findClosestCluster(ClusterHCA* object) {
    double bestDistance = -1;
    ClusterHCA* bestCHca = nullptr;
    if (grid->getMesh(object) == nullptr) {
        grid->update(object, object, 0);
    }

    vector<GeographicalObject*> voisins = grid->getMesh(object)->getNeighborObjects();
    for (unsigned int i=0; i<voisins.size(); i++) {
        GeographicalObject* chca = voisins[i];
        double distance = geoMetrics::distanceTo(chca, object, dataRef);
        if (bestDistance == -1 || distance <= bestDistance) {
            bestDistance = distance;
            bestCHca = this->clusters_hca[chca->name];
        }
    }
    return bestCHca;
}

/**
 * \brief 	Default constructor of class Hierarchical
 *
 * \param 	None
 * \return 	None
 */
void Hierarchical::mergeCluster(ClusterHCA* cluster1, ClusterHCA* cluster2) {
    ClusterHCA* newCluster = new ClusterHCA("cluster::"+str(this->addedClusters++), this);
    newCluster->addSubCluster(cluster1);
    newCluster->addSubCluster(cluster2);

    newCluster->computeCentroid();
    this->clusters_hca.insert(pair<string, ClusterHCA*>(newCluster->id, newCluster));
    this->clusters_hca.erase(cluster1->id);
    this->clusters_hca.erase(cluster2->id);
    if (grid->getMesh(cluster1) != nullptr) grid->getMesh(cluster1)->mapObjects.erase(cluster1->name);
    if (grid->getMesh(cluster2) != nullptr) grid->getMesh(cluster2)->mapObjects.erase(cluster2->name);
}

/**
 * \brief 	Default constructor of class Hierarchical
 *
 * \param 	None
 * \return 	None
 */
const std::unordered_map<string, GeologicCluster*>& Hierarchical::getClusters() {
    this->clusters.clear();
    ClusterHCA* chca = (clusters_hca.begin())->second;
    int currentMaxId = atoi(split(chca->id, "::")[1].c_str());
    unordered_map<int, ClusterHCA*> tempMap = {{currentMaxId, chca}};
    while (tempMap.size() < this->numberK) {
        ClusterHCA* toOpen = tempMap[currentMaxId];
        vector<ClusterHCA*> subClusters = toOpen->getSubClusters();
        for (unsigned int i=0; i<subClusters.size(); i++) {
            int openId = atoi(split(subClusters[i]->id, "::")[1].c_str());
            tempMap.insert(pair<int, ClusterHCA*>(openId, subClusters[i]));
        }
        tempMap.erase(currentMaxId);
        currentMaxId--;
    }

    unsigned int i = 0;
    unordered_map<int, ClusterHCA*>::iterator it = tempMap.begin();
    for (; it!=tempMap.end(); it++) {
        ClusterHCA* chca = it->second;
        chca->insertRecords();
        clusters.insert(pair<string, GeologicCluster*>("cluster::"+str(i++), std::move((GeologicCluster*) chca)));
    }
    return clusters;
}



