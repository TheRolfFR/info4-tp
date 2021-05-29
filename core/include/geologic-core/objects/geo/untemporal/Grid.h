/**
 * \file	Grid.h
 */

#ifndef GEOLOGICGRID_H
#define GEOLOGICGRID_H

#include "geologic-core/objects/geo/untemporal/GeographicalObject.h"
#include "geologic-core/objects/geo/untemporal/GridMesh.h"
#include "geologic-core/objects/geo/temporal/TemporalGeoPoint.h"
#include <memory>


class Grid {

    public:
        //*/ -------------------------------------------------
        Grid(OGRPoint* BL, double gridSize);
        Grid(const OGRPoint& BL, double gridSize);
        virtual ~Grid();

        //*/ -------------------------------------------------
        void meshEnv(int level=1);
        bool update(GeographicalObject* object, OGRPoint* newPosition, time_t t);
        bool update(GeographicalObject* object, TemporalGeoPoint* newPosition);
        GridMesh* getMesh(GeographicalObject* object, bool notSure=false);
        GridMesh* getMeshFromPoint(OGRPoint* location);
        void clearGrid(bool hard=false);

        std::vector<GridMesh*> getZeroMeshes();

        //*/ -------------------------------------------------
        std::unique_ptr<GridMesh> firstMesh;
        int meshingLevel = 1;

    private:
        std::unordered_map<GeographicalObject*, GridMesh*> locations;
};

#endif // GEOLOGICGRID_H
