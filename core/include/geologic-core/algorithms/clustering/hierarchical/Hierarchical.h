/**
 * \file	Hierarchical.h
 */

#ifndef HIERARCHICAL_H
#define HIERARCHICAL_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <unordered_set>
#include <unordered_map>
#include "geologic-core/algorithms/clustering/ClusteringEnvironment.h"
#include "geologic-core/algorithms/clustering/GeologicCluster.h"
#include "geologic-core/algorithms/clustering/hierarchical/ClusterHCA.h"
#include "geologic-core/objects/geo/untemporal/Grid.h"
#include <geologic-core/utils/customToolbox.h>


using namespace customToolbox;


class Hierarchical: public ClusteringEnvironment {

    public:
        //*/ -------------------------------------------------
        Hierarchical();
        virtual ~Hierarchical();

        //*/ -------------------------------------------------
        void startHCA(std::vector<GeographicalObject*>* population, unsigned int numberK);
        virtual const std::unordered_map<std::string, GeologicCluster*>& getClusters();

    private:
        //*/ -------------------------------------------------
        ClusterHCA* findClosestCluster(ClusterHCA* object);
        void mergeCluster(ClusterHCA* cluster1, ClusterHCA* cluster2);

        //*/ -------------------------------------------------
        unsigned int numberK;
        unsigned int addedClusters;
        std::unordered_map<std::string, ClusterHCA*> clusters_hca;
        Grid* grid;
};

#endif // HIERARCHICAL_H
