/**
 * \file	Kmeans.h
 */

#ifndef KMEANS_H
#define KMEANS_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include "geologic-core/algorithms/clustering/ClusteringEnvironment.h"
#include "geologic-core/algorithms/clustering/kmeans/ClusterKmeans.h"
#include <geologic-core/utils/customToolbox.h>


using namespace customToolbox;


class Kmeans: public ClusteringEnvironment {

    public:
        //*/ -------------------------------------------------
        Kmeans();
        virtual ~Kmeans();

        //*/ -------------------------------------------------
        void startKmeans(std::vector<GeographicalObject*>* population, unsigned int numberK);
        virtual const std::unordered_map<std::string, GeologicCluster*>& getClusters();

        double percStill;

    private:
        //*/ -------------------------------------------------
        ClusterKmeans* findClosestCluster(GeographicalObject* object);

        //*/ -------------------------------------------------
        unsigned int numberK;
        std::unordered_map<std::string, ClusterKmeans*> clusters_kmeans;
};

#endif // KMEANS_H
