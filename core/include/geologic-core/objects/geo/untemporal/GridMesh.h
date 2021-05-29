/**
 * \file	GridMesh.h
 */

#ifndef GRIDMESH_H
#define GRIDMESH_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <ogr_geometry.h>
#include <geologic-core/objects/geo/untemporal/GeographicalObject.h>
#include <geologic-core/objects/geo/temporal/TemporalGeoPoint.h>

class GridMesh {

    public:
        //*/ -------------------------------------------------
        GridMesh();
        virtual ~GridMesh();

        GridMesh(OGRPoint* BL, double pdm, GridMesh* parent=nullptr);
        GridMesh(const OGRPoint& BL, double pdm, GridMesh* parent=nullptr);

        //*/ -------------------------------------------------
        void subdivise(int level);
        GridMesh* update(GeographicalObject* object, OGRPoint* newPosition, time_t t, GridMesh* lastMesh);

        unsigned int getNumPoints();
        std::shared_ptr<OGRPoint> getPoint(unsigned int pointId);
        bool containsPoint(OGRPoint* point);

        std::vector<GridMesh*> getNeighbors();
        std::vector<GeographicalObject*> getNeighborObjects(bool strict=false);
        std::vector<GeographicalObject*> getSubObjects();

        GridMesh* searchUD(OGRPoint* pos, GridMesh* caller, int currentLevel);
        GridMesh* search(OGRPoint* pos);

        void clearGrid(bool hard=false);

        void getZeroMeshes(std::vector<GridMesh*>& rVec);

        //*/ -------------------------------------------------
        OGRPoint meshPos;
        GridMesh* parent;

        OGRLinearRing way;
        double pdm;
        int _level;
        time_t canDisplay;

        std::unordered_map<std::string, GeographicalObject*> mapObjects; // The list of all vehicles within that mesh
        std::vector<GridMesh*> subMeshes; // The list of all included meshes (can be 0 at last level)

};

#endif // GRIDMESH_H
