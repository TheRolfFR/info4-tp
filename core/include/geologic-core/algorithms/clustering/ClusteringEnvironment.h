/**
 * \file	ClusteringEnvironment.h
 */

#ifndef CLUSTERINGENVIRONMENT_H
#define CLUSTERINGENVIRONMENT_H

#include "geologic-core/core/geologic-launcher/CoordinateSystemManager.h"
#include "geologic-core/objects/geo/untemporal/Bbox.h"
#include "geologic-core/algorithms/clustering/GeologicCluster.h"
#include <chrono>
#include <ctime>


class ClusteringEnvironment {

    public:
        //*/ -------------------------------------------------
        ClusteringEnvironment();
        virtual ~ClusteringEnvironment();

        //*/ -------------------------------------------------
        virtual const std::unordered_map<std::string, GeologicCluster*>& getClusters();
        void setDataRef(OGRSpatialReference* dataRef);

        Bbox& getBbox();
        OGRSpatialReference* getDataRef();

    protected:
        //*/ -------------------------------------------------
        void clearCluster();

        //*/ -------------------------------------------------
        OGRSpatialReference* dataRef;
        Bbox bbox;
        std::unordered_map<std::string, GeologicCluster*> clusters;
        std::vector<GeographicalObject*> population;
};

#endif // CLUSTERINGENVIRONMENT_H
