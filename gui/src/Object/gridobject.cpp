/**
 * \file	gridobject.cpp
 * \class	VehiclePosition
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/01/2018
 * \brief	GridObject is a class representing a GridObject
 */

#include <Object/gridobject.h>
#include <cstdio>


#include <ResourceManagement/datamanager.h>


using namespace std;


/**
 * \brief 	Default constructor of class GridObject
 *
 * \param 	None
 * \return 	None
 */
GridObject::GridObject(View* view, std::shared_ptr<Shader> shader, Grid* grid) : ChildObject(view, "Grid Object", shader) {
    this->grid = grid;

    m_data = DataManager::getInstance()->get("Grid");
}

/**
 * \brief 	Default destructor of class GridObject
 *
 * \param 	None
 * \return 	None
 */
GridObject::~GridObject() {}

/**
 * \brief 	Inherited method from class Object
 *
 * \param 	None
 * \return 	None
 */
//void GridObject::draw() {}

/**
 * \brief 	Inherited method from class Object
 *
 * \param 	t   a time_t
 * \return 	None
 *
 */
/*void GridObject::draw(unsigned long long t) {

//    vector<GridMesh*> vec = this->grid->getZeroMeshes();
//    for (unsigned int i=0; i<vec.size(); i++) {
//        MeshObject md(vec[i]);
//        md.draw(t);
//    }

    int levels = (1 << grid->meshingLevel) + 1;
    double meshSize = grid->firstMesh->pdm / levels; // (initial PDM) / (2^(level))

    double minX = grid->firstMesh->getPoint(0)->getX();
    double minY = grid->firstMesh->getPoint(0)->getY();
    double maxX = grid->firstMesh->getPoint(2)->getX();
    double maxY = grid->firstMesh->getPoint(2)->getY();

    OGRPoint ptA (minX, minY);
    OGRPoint ptB (minX, maxY);

    glLineWidth(2);
    glColor4d(0, 0, 1, 0.6); //09
    glBegin(GL_LINES);
    for (unsigned int i=0; i<levels; i++) {
        glVertex3d(ptA.getX(), ptA.getY(), 0.0);
        glVertex3d(ptB.getX(), ptB.getY(), 0.0);
        ptA.setX(ptA.getX()+meshSize);
        ptB.setX(ptB.getX()+meshSize);
    }
    glVertex3d(ptA.getX(), ptA.getY(), 0.0);
    glVertex3d(ptB.getX(), ptB.getY(), 0.0);
    glEnd();

    ptA.setX(minX);
    ptA.setY(maxY);
    glBegin(GL_LINES);
    for (unsigned int i=0; i<levels; i++) {
        glVertex3d(ptA.getX(), ptA.getY(), 0.0);
        glVertex3d(ptB.getX(), ptB.getY(), 0.0);
        ptA.setY(ptA.getY()-meshSize);
        ptB.setY(ptB.getY()-meshSize);
    }
    glVertex3d(ptA.getX(), ptA.getY(), 0.0);
    glVertex3d(ptB.getX(), ptB.getY(), 0.0);
    glEnd();
}*/
