/**
 * \file	DBscan.cpp
 * \class   DBscan
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/05/2015
 * \brief	Methods of Kmeans object
 *
 * Methods of DBscan object
 */

#include "geologic-core/algorithms/clustering/dbscan/DBscan.h"

using namespace std;
using namespace customToolbox;
using namespace std::chrono;


/**
 * \brief 	Default constructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
DBscan::DBscan() {
    this->radius = pair<string, double>("percentage", 0.01);
    this->minNeighbors = 3;
    srand(time(nullptr));
    this->grid = nullptr;
}

/**
 * \brief 	Default destructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
DBscan::~DBscan() {
    this->clear(true);
}

/**
 * \brief 	Default constructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
void DBscan::startDBscan(std::vector<GeographicalObject*>* population, std::pair<string, double> radius, unsigned int minNeighbors) {
    //*/ -------------------------------------------------
    this->clear(true);

    //*/ -------------------------------------------------
    this->radius = radius;
    this->minNeighbors = minNeighbors;

    if (population == nullptr) return;
    if (population->size() <= 0) return;
    for (unsigned int i=0; i<population->size(); i++) {
        bbox.update(population->at(i));
        this->population.push_back(population->at(i));
        this->notVisited.insert(population->at(i));
    }

    double diagDist = geoMetrics::distanceTo(bbox.getBL().get(), bbox.getTR().get(), this->getDataRef());
    double min_pdm = radius.second;
    if (radius.first == "percentage") min_pdm = radius.second*diagDist;

    double longDist = geoMetrics::distanceTo(bbox.getBL().get(), bbox.getBR().get(), this->getDataRef())+min_pdm;
    double heigDist = geoMetrics::distanceTo(bbox.getBL().get(), bbox.getTL().get(), this->getDataRef())+min_pdm;
    double envSize = std::max(longDist, heigDist);
    if (envSize <= 0) envSize = 1;
    this->grid = new Grid(bbox.getBL().get(), envSize);
    // min_pdm = (envSize) / (2^(level))
    // => level = log(envSize / min_pdm) / log(2)

    this->grid->meshEnv(std::round(std::log10(envSize/min_pdm)/std::log10(2)));
    for (unsigned int i=0; i<population->size(); i++) this->grid->update(this->population[i], this->population[i], 0);

    GeologicCluster* cdb = new GeologicCluster("cluster::noise", this);
    clusters.insert(pair<string, GeologicCluster*>(cdb->id, cdb));

    if (population->size() <= 0) return;
    //*/ -------------------------------------------------
    //cout << "Running DBscan..." << endl;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (this->notVisited.size() > 0) {
        /*/
        cout << "At main while: visited are :";
        for (auto i: visited) {
            cout << " " << i->name;
        }
        cout << endl;
        cout << "At main while: Notvisited are :";
        for (auto i: notVisited) {
            cout << " " << i->name;
        }
        cout << endl;
        //*/

        GeographicalObject* currentObject = *(this->notVisited.begin());
        //cout << "Checking " << currentObject->name << endl;
        this->notVisited.erase(this->notVisited.begin());
        this->visited.insert(currentObject);
        //cout << "getNeigh 1" << endl;
        unordered_set<GeographicalObject*> neighbors = this->getNeighbors(currentObject);
        GeologicCluster* currentCluster = clusters["cluster::noise"];
        if (neighbors.size() >= this->minNeighbors) {
            string clusterName = "cluster::"+str(this->clusters.size()-1);
            currentCluster = new GeologicCluster(clusterName, this);
            clusters.insert(pair<string, GeologicCluster*>(currentCluster->id, currentCluster));
            this->expandCluster(currentCluster, neighbors);
        }
        currentCluster->addObject(currentObject);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double, std::milli> time_span = t2 - t1;
    //cout << "DBscan done. " << "It took me " << time_span.count() << " milliseconds." << endl;

    this->clear();
}

/**
 * \brief 	Default constructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
unordered_set<GeographicalObject*> DBscan::getNeighbors(GeographicalObject* object) {
    //This class must be optimized using meshedgird
    unordered_set<GeographicalObject*> tempSet;
    //tempSet.insert(object);
    if (grid->getMesh(object) == nullptr) {
        grid->update(object, object, 0);
    }
    vector<GeographicalObject*> voisins = grid->getMesh(object)->getNeighborObjects();
    for (unsigned int i=0; i<voisins.size(); i++) {
        //for (unsigned int i=0; i<this->population.size(); i++) {
        //if (this->population[i] != object) {
        if (voisins[i] != object) {
            double diagDist = geoMetrics::distanceTo(bbox.getBL().get(), bbox.getTR().get(), dataRef);
            double minDist = radius.second;
            if (radius.first == "percentage") minDist = radius.second*diagDist;
            /*/
            cout << "object: " << object->getX() << ", " << object->getY() << endl;
            cout << "voisin: " << voisins[i]->getX() << ", " << voisins[i]->getY() << endl;
            cout << "mindist:: " << minDist << "  currentDist = " << geoMetrics::distanceTo(voisins[i], object, dataRef) << endl;
            //*/
            if (geoMetrics::distanceTo(voisins[i], object, dataRef) < minDist) {
                tempSet.insert(voisins[i]);
            }
        }
    }
    /*/
    cout << "Neighbors of " << object->name << " :";
    for (auto i: tempSet) {
        cout << " " << i->name;
    }
    cout << endl;
    //*/
    return tempSet;


}

/**
 * \brief 	Default constructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
void DBscan::expandCluster(GeologicCluster* currentCluster, unordered_set<GeographicalObject*>& neighbors) {

    //cout << "Expanding cluster " << currentCluster->id << endl;
    while (neighbors.size() > 0) {
        GeographicalObject* record = *(neighbors.begin());
        neighbors.erase(neighbors.begin());
        //cout << "Chosing " << record->name << " from neighbors" << endl;

        if (this->visited.find(record) == this->visited.end()) {
            this->visited.insert(record);
            /*/
            cout << record->name << " hasnt been visited yet" << endl;
            cout << "getNeig of " << record->name << endl;
            //*/
            unordered_set<GeographicalObject*> otherNeighbors = this->getNeighbors(record);
            if (otherNeighbors.size() >= this->minNeighbors) {
                neighbors.insert(otherNeighbors.begin(), otherNeighbors.end());

                /*/
                cout << "Number of nighbors ok, we add them" << endl;
                cout << "Total neighbors are :";
                for (auto i: neighbors) {
                    cout << " " << i->name;
                }
                cout << endl;
                //*/
            }
        } /*/
            else {
            cout << record->name << " has been visited already" << endl;
        }
        //*/

        if (this->notVisited.find(record) != this->notVisited.end()) {
            //cout << record->name << " is wihtin NotVisited set. We remove it from NotVisited, and add it to the cluster " << currentCluster->id << endl;
            this->notVisited.erase(record);
            currentCluster->addObject(record);
        }
    }
}

/**
 * \brief 	Default constructor of class Kmeans
 *
 * \param 	None
 * \return 	None
 */
void DBscan::clear(bool hard) {
    if (hard) {
        this->clearCluster();
        this->population.clear();
    }
    this->bbox.clear();

    if (this->grid != nullptr) delete(this->grid);
    this->grid = nullptr;

    this->visited.clear();
    this->notVisited.clear();
}
