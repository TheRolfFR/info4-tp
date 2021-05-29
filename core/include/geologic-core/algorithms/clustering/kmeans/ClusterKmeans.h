/**
 * \file	ClusterKmeans.h
 */

#ifndef ClusterKmeans_H
#define ClusterKmeans_H

#include <map>
#include <string>
#include <vector>
#include "geologic-core/utils/customToolbox.h"
#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"
#include "geologic-core/objects/geo/untemporal/GeographicalObject.h"
#include "geologic-core/algorithms/clustering/GeologicCluster.h"

using namespace customToolbox;

class Kmeans;

class ClusterKmeans: public GeologicCluster {

    public:
        //*/ -------------------------------------------------
        ClusterKmeans(std::string id, Kmeans* parent);
        virtual ~ClusterKmeans();

        //*/ -------------------------------------------------
        void generateRandomCentroid();
        virtual bool computeCentroid();
        virtual void clearRecords();

    private:
        //*/ -------------------------------------------------
        double diagDist;
        double percStill;
};

#endif // ClusterKmeans_H
