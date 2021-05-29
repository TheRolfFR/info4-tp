/**
 * \file	gridMeshManager.cpp
 * \class	gridMeshManager
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/01/2018
 * \brief	gridMeshManager is managing all the meshes of the environment
 */

#include "geologic-core/objects/geo/untemporal/Grid.h"

using namespace std;

/**
 * \brief 	Default constructor of class gridMeshManager
 *
 * \param 	None
 * \return 	None
 */
Grid::Grid(OGRPoint* BL, double gridSize) {
    firstMesh = unique_ptr<GridMesh>(new GridMesh(BL, gridSize));
}

/**
 * \brief 	Default constructor of class gridMeshManager
 *
 * \param 	None
 * \return 	None
 */
Grid::Grid(const OGRPoint& BL, double gridSize) {
    firstMesh = unique_ptr<GridMesh>(new GridMesh(BL, gridSize));
}

/**
 * \brief 	Default destructor of class gridMeshManager
 *
 * \param 	None
 * \return 	None
 */
Grid::~Grid() {}

/**
 * \brief 	Starts meshing the environement
 *
 * \param 	level   The number of division to have in the environement
 * \return 	None
 * Lets keep it simple, no more than 8 levels of subdivision
 */
void Grid::meshEnv(int level) {
    if (level > 8) level = 8;
    meshingLevel = level;
    firstMesh->subdivise(level);
}

/**
 * \brief 	Update the position of a specific vehicle in the environement
 *
 * \param 	vehId   The vehicle Id
 * \param   veh     The address of the Vehicle
 * \param   position    The current position of the Vehicle
 * \param   t       The current time of update (to allow displaying of mesh)
 * \return 	None
 */
bool Grid::update(GeographicalObject* object, OGRPoint* newPosition, time_t t) {
    GridMesh* lastMesh = nullptr;
    if (locations.find(object) != locations.end()) {
        lastMesh = locations[object];
        if (lastMesh->containsPoint(newPosition)) return true;
    }

    GridMesh* newMesh = firstMesh->update(object, newPosition, t, lastMesh);
    if (newMesh != nullptr) {
        locations[object] = newMesh;
        return true;
    } else if (lastMesh != nullptr) {
        locations.erase(object);
    }
    return false;
}

/**
 * \brief 	Update the position of a specific vehicle in the environement
 *
 * \param 	vehId   The vehicle Id
 * \param   veh     The address of the Vehicle
 * \param   position    The current position of the Vehicle
 * \param   t       The current time of update (to allow displaying of mesh)
 * \return 	None
 */
bool Grid::update(GeographicalObject* object, TemporalGeoPoint* newPosition) {
   return this->update(object, newPosition, newPosition->timestamp);
}

/**
 * \brief 	Update the position of a specific vehicle in the environement
 *
 * \param 	vehId   The vehicle Id
 * \param   veh     The address of the Vehicle
 * \param   position    The current position of the Vehicle
 * \param   t       The current time of update (to allow displaying of mesh)
 * \return 	None
 */
GridMesh* Grid::getMesh(GeographicalObject* object, bool notSure) {
    if (locations.find(object) != locations.end()) return locations[object];
    if (notSure) return firstMesh->search(object);
    return nullptr;
}

/**
 * \brief 	Update the position of a specific vehicle in the environement
 *
 * \param 	vehId   The vehicle Id
 * \param   veh     The address of the Vehicle
 * \param   position    The current position of the Vehicle
 * \param   t       The current time of update (to allow displaying of mesh)
 * \return 	None
 */
GridMesh* Grid::getMeshFromPoint(OGRPoint* location) {
    return firstMesh->search(location);
}

/**
 * \brief 	Update the position of a specific vehicle in the environement
 *
 * \param 	vehId   The vehicle Id
 * \param   veh     The address of the Vehicle
 * \param   position    The current position of the Vehicle
 * \param   t       The current time of update (to allow displaying of mesh)
 * \return 	None
 */
void Grid::clearGrid(bool hard) {
    firstMesh->clearGrid(hard);
}

/**
 * \brief 	Update the position of a specific vehicle in the environement
 *
 * \param 	vehId   The vehicle Id
 * \param   veh     The address of the Vehicle
 * \param   position    The current position of the Vehicle
 * \param   t       The current time of update (to allow displaying of mesh)
 * \return 	None
 */
vector<GridMesh*> Grid::getZeroMeshes() {
    vector<GridMesh*> rVec;
    firstMesh->getZeroMeshes(rVec);
    return rVec;
}
