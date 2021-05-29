/**
 * \file	GeologicCluster.h
 */

#ifndef GeologicCluster_H
#define GeologicCluster_H

#include <map>
#include <string>
#include <vector>
#include "geologic-core/utils/customToolbox.h"
#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"
#include "geologic-core/objects/geo/untemporal/GeographicalObject.h"

using namespace customToolbox;

class ClusteringEnvironment;

class GeologicCluster: public GeographicalObject {

    public:
        //*/ -------------------------------------------------
        GeologicCluster(std::string id, ClusteringEnvironment* env);
        virtual ~GeologicCluster();

        //*/ -------------------------------------------------
        void addObject(GeographicalObject* object);
        virtual bool computeCentroid();
        virtual void clearRecords();

        //*/ -------------------------------------------------
        std::string id;
        ClusteringEnvironment* env;
        std::vector<GeographicalObject*> records;

};

#endif // ClusterKmeans_H
