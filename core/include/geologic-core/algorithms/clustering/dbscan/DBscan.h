/**
 * \file	DBscan.h
 */

#ifndef DBSCAN_H
#define DBSCAN_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <unordered_set>
#include <unordered_map>
#include "geologic-core/algorithms/clustering/ClusteringEnvironment.h"
#include "geologic-core/algorithms/clustering/GeologicCluster.h"
#include "geologic-core/objects/geo/untemporal/Grid.h"
#include <geologic-core/utils/customToolbox.h>


using namespace customToolbox;


class DBscan: public ClusteringEnvironment {

    public:
        //*/ -------------------------------------------------
        DBscan();
        virtual ~DBscan();

        //*/ -------------------------------------------------
        void startDBscan(std::vector<GeographicalObject*>* population, std::pair<std::string, double> radius, unsigned int minNeighbors);
        void clear(bool hard=false);

    private:
        //*/ -------------------------------------------------
        std::pair<std::string, double> radius;
        unsigned int minNeighbors;

        Grid* grid;

        std::unordered_set<GeographicalObject*> getNeighbors(GeographicalObject* object);
        void expandCluster(GeologicCluster* currentCluster, std::unordered_set<GeographicalObject*>& neighbors);

        std::unordered_set<GeographicalObject*> notVisited;
        std::unordered_set<GeographicalObject*> visited;
};

#endif // KMEANS_H
