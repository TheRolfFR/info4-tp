/**
 * \file	gridData.cpp
 * \class	GridData
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/01/2018
 * \brief	GridData is a class representing a GridData
 */

#include <Data/griddata.h>
#include <cstdio>

using namespace std;


/**
 * \brief 	Default constructor of class GridData
 *
 * \param 	None
 * \return 	None
 */
GridData::GridData() : Data("Grid Data") {
    std::vector<float> vertices = {0,0,0};

    setVertices(vertices);
    setStructureType(GL_POINTS);
}

/**
 * \brief 	Default destructor of class GridData
 *
 * \param 	None
 * \return 	None
 */
GridData::~GridData() {}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	None
 * \return 	None
 */
//void GridData::draw() {}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	t   a time_t
 * \return 	None
 *
 */
/*void GridData::draw(unsigned long long t) {

//    vector<GridMesh*> vec = this->grid->getZeroMeshes();
//    for (unsigned int i=0; i<vec.size(); i++) {
//        MeshData md(vec[i]);
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
