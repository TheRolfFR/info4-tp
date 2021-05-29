/**
 * \file	GridMesh.cpp
 * \class	GridMesh
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/01/2018
 * \brief	GridMesh is a mesh represention used to quickly retrieve all Vehicle within a certain range
 */

#include "geologic-core/objects/geo/untemporal/GridMesh.h"

using namespace std;


/**
 * \brief 	Default constructor of class gridmesh
 *
 * \param 	None
 * \return 	None
 */
GridMesh::GridMesh() {
    this->parent = nullptr;
    this->pdm = 1;
    this->meshPos = OGRPoint(0, 0, 0);
    this->way = OGRLinearRing(0);
    this->canDisplay = 0;
    this->_level = 0;
}

/**
 * \brief 	Constructor with parameters of class gridmesh
 *
 * \param 	BL  The address of an OGRPoint, the Bottom-Left position of this mesh
 * \param   pdm The size of this mesh
 * \param   parent  The address of the parent of this mesh (upper mesh)
 * \return 	None
 * Creates a ring with the BL position and the pdm.
 */
GridMesh::GridMesh(OGRPoint* BL, double pdm, GridMesh* parent) {
    this->parent = parent;
    this->pdm = pdm;
    if (this->pdm <= 0) this->pdm = 1;
    this->meshPos.setX(BL->getX());
    this->meshPos.setY(BL->getY());

    OGRPoint TL = OGRPoint(meshPos.getX(), meshPos.getY()+pdm, 0.0);
    OGRPoint TR = OGRPoint(meshPos.getX()+pdm, meshPos.getY()+pdm, 0.0);
    OGRPoint BR = OGRPoint(meshPos.getX()+pdm, meshPos.getY(), 0.0);

    way.addPoint(&this->meshPos);
    way.addPoint(&TL);
    way.addPoint(&TR);
    way.addPoint(&BR);
    if (!bool(way.get_IsClosed())) way.closeRings();
    this->canDisplay = 0;
    this->_level = 0;
    if (this->parent != nullptr) this->_level = this->parent->_level+1;
}

/**
 * \brief 	Constructor with parameters of class gridmesh
 *
 * \param 	BL  The address of an OGRPoint, the Bottom-Left position of this mesh
 * \param   pdm The size of this mesh
 * \param   parent  The address of the parent of this mesh (upper mesh)
 * \return 	None
 * Creates a ring with the BL position and the pdm.
 */
GridMesh::GridMesh(const OGRPoint& BL, double pdm, GridMesh* parent) {
    this->parent = parent;
    this->pdm = pdm;
    if (this->pdm <= 0) this->pdm = 1;
    this->meshPos.setX(BL.getX());
    this->meshPos.setY(BL.getY());

    OGRPoint TL = OGRPoint(meshPos.getX(), meshPos.getY()+pdm, 0.0);
    OGRPoint TR = OGRPoint(meshPos.getX()+pdm, meshPos.getY()+pdm, 0.0);
    OGRPoint BR = OGRPoint(meshPos.getX()+pdm, meshPos.getY(), 0.0);

    way.addPoint(&this->meshPos);
    way.addPoint(&TL);
    way.addPoint(&TR);
    way.addPoint(&BR);
    if (!bool(way.get_IsClosed())) way.closeRings();
    this->canDisplay = 0;
    this->_level = 0;
    if (this->parent != nullptr) this->_level = this->parent->_level+1;
}

/**
 * \brief 	Default destructor of class gridmesh
 *
 * \param 	None
 * \return 	None
 */
GridMesh::~GridMesh() {
    this->parent = nullptr;
    for (unsigned int i=0; i<subMeshes.size(); i++) {
        if (subMeshes[i] != nullptr) delete(subMeshes[i]);
        subMeshes[i] = nullptr;
    }
    subMeshes.clear();
    mapObjects.clear();
}

/**
 * \brief 	Divides a mesh into 4 smaller meshes
 *
 * \param 	level   The division level (for recursive division)
 * \return 	None
 * Creates 4 new gridmesh and adds them to the subMeshes vector.
 * A call to subdivise(1) divides a mesh into 4 meshes (1 division)
 * A cal to subdivise(2) divides a mesh into 4 mehshes, each divided into 4 meshes, for a total of 16 submeshes at lowest level
 * The total is: 4^(level) meshes at lowest level
 * And: pdm = (initial PDM) / (2^(level)) meters
 */
void GridMesh::subdivise(int level) {
    if (level <= 0) return;
    double newPdm = this->pdm/2.0;

    // New mesh at Bottom-Left position
    OGRPoint ptBL = OGRPoint(this->meshPos.getX(), this->meshPos.getY(), 0.0);
    GridMesh* mBL = new GridMesh(&ptBL, newPdm, this);
    subMeshes.push_back(mBL);
    mBL->subdivise((level-1)); // Recursive call to divide

    // New mesh at Top-Left position
    OGRPoint ptTL = OGRPoint(this->meshPos.getX(), this->meshPos.getY()+newPdm, 0.0);
    GridMesh* mTL = new GridMesh(&ptTL, newPdm, this);
    subMeshes.push_back(mTL);
    mTL->subdivise((level-1));

    // New mesh at Top-Right position
    OGRPoint ptTR = OGRPoint(this->meshPos.getX()+newPdm, this->meshPos.getY()+newPdm, 0.0);
    GridMesh* mTR = new GridMesh(&ptTR, newPdm, this);
    subMeshes.push_back(mTR);
    mTR->subdivise((level-1));

    // New mesh at Bottom-Right position
    OGRPoint ptBR = OGRPoint(this->meshPos.getX()+newPdm, this->meshPos.getY(), 0.0);
    GridMesh* mBR = new GridMesh(&ptBR, newPdm, this);
    subMeshes.push_back(mBR);
    mBR->subdivise((level-1));
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
GridMesh* GridMesh::update(GeographicalObject* object, OGRPoint* newPosition, time_t t, GridMesh* lastMesh) {
    // We update the list of vehicles only for meshes at lowest level (the vehicle only knows the address of a lowest mesh    
    if (this->subMeshes.size() > 0) {
        for (unsigned int i=0; i<subMeshes.size(); i++)
            if (subMeshes[i]->containsPoint(newPosition)) return subMeshes[i]->update(object, newPosition, t, lastMesh);
    } else {
        // If the mesh contains the position of the vehicle
        if (containsPoint(newPosition)) {
            // If the vehicle was already wihtin this mesh at time t-1
            if (mapObjects.find(object->name) == mapObjects.end()) {
                // We advise the last gridMesh of the vehicle to remove it, and we add that vehicle into the current mesh
                if (lastMesh != nullptr && lastMesh != this) lastMesh->mapObjects.erase(object->name);
                mapObjects.insert(pair<string, GeographicalObject*>(object->name, object));
            }

            //*/ -------------------------------------------------
            // We update the display behavior of the meshes
            /*/
            this->canDisplay = t; // We can display the current mesh at time t
            vector<GridMesh*> neig = this->getNeighbors(); // For all the 8 neighbors of that mesh
            for (unsigned int i=0; i<neig.size(); i++) {
                neig[i]->canDisplay = t; // We can also display them
            }
            //*/
            return this;
        }
    }
    return nullptr;
}

/**
 * \brief 	Gets back the number of points into that shape
 *
 * \param 	None
 * \return 	the number of points of that shape
 */
unsigned int GridMesh::getNumPoints() {
   return (unsigned int) way.getNumPoints();
}

/**
 * \brief 	Gets back a specific point of the shape
 *
 * \param 	pointId The id of the point to get back
 * \return 	The address of the point to get back
 */
shared_ptr<OGRPoint> GridMesh::getPoint(unsigned int pointId) {
    shared_ptr<OGRPoint> returnPoint = make_shared<OGRPoint>();
    way.getPoint(pointId, returnPoint.get());
    return returnPoint;
}

/**
 * \brief 	Checks if a point is located within that shape
 *
 * \param 	point   The address of a point
 * \return 	True if the point is located within that shape, false otherwise.
 */
bool GridMesh::containsPoint(OGRPoint* point) {
    return way.isPointInRing(point);
}

/**
 * \brief 	Gets back the neighbors of that mesh
 *
 * \param 	None
 * \return 	A vector with the addresses of the adjacent meshes (only at lowest level)
 */
vector<GridMesh*> GridMesh::getNeighbors() {
    vector<GridMesh*> returnVect;
    //is not possible for the moment for not bottom levels
    //if (this->subMeshes.size() == 0) {
        //first we compute the 8 positions of the neighbors
    if (parent != nullptr) {
        for (int i=-1; i<=1; i++) {
            for (int j=-1; j<=1; j++) {
                if (i!=0 || j!=0) {
                    OGRPoint tmp = OGRPoint(meshPos.getX()+(i*pdm)+(pdm/2.0), meshPos.getY()+(j*pdm)+(pdm/2.0), 0.0);
                    GridMesh* voisin = parent->searchUD(&tmp, this, this->_level);
                    if (voisin != nullptr) {
                        returnVect.push_back(voisin);
                    }
                }
            }
        }
    } else {
        returnVect.push_back(this);
    }
    return returnVect;
}

/**
 * \brief 	Gets back all the vehicles in the neighborhood of that mesh
 *
 * \param 	None
 * \return 	A vector with the addresses of the vehicles contained in the adjacent meshes (only at lowest level)
 */
vector<GeographicalObject*> GridMesh::getNeighborObjects(bool strict) {
    vector<GeographicalObject*> returnVect = this->getSubObjects();
    vector<GridMesh*> neig = getNeighbors();
    for (unsigned int i=0; i<neig.size(); i++) {
        vector<GeographicalObject*> tmp = neig[i]->getSubObjects();
        returnVect.insert(returnVect.end(), tmp.begin(), tmp.end());
    }

    if (!strict && returnVect.size() <= 0 && this->parent != nullptr) return parent->getNeighborObjects();
    return returnVect;
}

/**
 * \brief 	Gets back all the vehicles in the neighborhood of that mesh
 *
 * \param 	None
 * \return 	A vector with the addresses of the vehicles contained in the adjacent meshes (only at lowest level)
 */
vector<GeographicalObject*> GridMesh::getSubObjects() {
    vector<GeographicalObject*> returnVect;
    if (this->subMeshes.size() <= 0) {
        unordered_map<string, GeographicalObject*>::iterator it = mapObjects.begin();
        for (; it!=mapObjects.end(); it++) {
            GeographicalObject* obj = it->second;
            returnVect.push_back(obj);
        }
    } else {
        for (unsigned int i=0; i<subMeshes.size(); i++) {
            vector<GeographicalObject*> tmp = subMeshes[i]->getSubObjects();
            returnVect.insert(returnVect.end(), tmp.begin(), tmp.end());
        }
    }
    return returnVect;
}

/**
 * \brief 	Gets back the address of a mesh at lowest level containing a specific position
 *
 * \param 	pos The location to check
 * \param   caller  The address of the caller (to avoid unecessary recursive calls)
 * \return 	The address of the mesh containg that position. nullptr if not found in the grid.
 */
GridMesh* GridMesh::searchUD(OGRPoint* pos, GridMesh* caller, int currentLevel) {
    if (containsPoint(pos)) {
        if (this->subMeshes.size() <= 0 || this->_level == currentLevel) return this;
        for (unsigned int i=0; i<subMeshes.size(); i++) {
            if (caller != subMeshes[i]) { //don't ask your caller
                GridMesh* retgm = subMeshes[i]->searchUD(pos, this, currentLevel);
                if (retgm != nullptr) return retgm;
            }
        }
    } else {
        if (parent != nullptr && caller != parent) return parent->searchUD(pos, this, currentLevel); //don't ask your caller
    }
    return nullptr;
}

/**
 * \brief 	Gets back the address of a mesh at lowest level containing a specific position
 *
 * \param 	pos The location to check
 * \param   caller  The address of the caller (to avoid unecessary recursive calls)
 * \return 	The address of the mesh containg that position. nullptr if not found in the grid.
 */
GridMesh* GridMesh::search(OGRPoint* pos) {
    if (containsPoint(pos)) {
        if (this->subMeshes.size() <= 0) return this;
        for (unsigned int i=0; i<subMeshes.size(); i++) {
            if (subMeshes[i]->containsPoint(pos)) return subMeshes[i]->search(pos);
        }
    }
    return nullptr;
}

/**
 * \brief 	Gets back the address of a mesh at lowest level containing a specific position
 *
 * \param 	pos The location to check
 * \param   caller  The address of the caller (to avoid unecessary recursive calls)
 * \return 	The address of the mesh containg that position. nullptr if not found in the grid.
 */
void GridMesh::clearGrid(bool hard) {
    if (this->subMeshes.size() > 0) {
        for (unsigned int i=0; i<subMeshes.size(); i++) {
            subMeshes[i]->clearGrid(hard);
        }
    }
    if (hard) {
        unordered_map<string, GeographicalObject*>::iterator it = mapObjects.begin();
        while (it != mapObjects.end()) {
            if (it->second != nullptr) delete(it->second);
            it->second = nullptr;
            it++;
        }
    }
    this->mapObjects.clear();
}

/**
 * \brief 	Gets back the address of a mesh at lowest level containing a specific position
 *
 * \param 	pos The location to check
 * \param   caller  The address of the caller (to avoid unecessary recursive calls)
 * \return 	The address of the mesh containg that position. nullptr if not found in the grid.
 */
void GridMesh::getZeroMeshes(vector<GridMesh*>& rVec) {
    if (this->subMeshes.size() > 0) {
        for (unsigned int i=0; i<subMeshes.size(); i++) {
            subMeshes[i]->getZeroMeshes(rVec);
        }
    } else {
        rVec.push_back(this);
    }
}
