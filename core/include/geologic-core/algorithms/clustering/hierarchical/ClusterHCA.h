/**
 * \file	ClusterHCA.h
 */

#ifndef CLUSTERHIERARCHICAL_H
#define CLUSTERHIERARCHICAL_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <unordered_set>
#include <unordered_map>
#include "geologic-core/algorithms/clustering/ClusteringEnvironment.h"
#include "geologic-core/algorithms/clustering/GeologicCluster.h"
#include <geologic-core/utils/customToolbox.h>


using namespace customToolbox;

class Hierarchical;

class ClusterHCA: public GeologicCluster {

    public:
        //*/ -------------------------------------------------
        ClusterHCA(std::string id, Hierarchical* parent);
        virtual ~ClusterHCA();

        //*/ -------------------------------------------------
        const std::vector<ClusterHCA*>& getSubClusters();
        void addSubCluster(ClusterHCA* c);
        virtual bool computeCentroid();
        void insertRecords();

    private:
        //*/ -------------------------------------------------
        std::vector<GeographicalObject*> getHCARecords();

        //*/ -------------------------------------------------
        std::vector<ClusterHCA*> subClusters;

};

#endif // CLUSTERHIERARCHICAL_H
