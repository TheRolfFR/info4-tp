/**
 * \file	meshData.cpp
 * \class	VehiclePosition
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/01/2018
 * \brief	meshData is a class representing a meshData
 */

#include <Data/meshdata.h>

using namespace std;


/**
 * \brief 	Default constructor of class MeshData
 *
 * \param 	None
 * \return 	None
 */
MeshData::MeshData() : Data("Mesh Data") {
    std::vector<float> vertices = {0,0,0};

    setVertices(vertices);
    setStructureType(GL_POINTS);
}

/**
 * \brief 	Default destructor of class MeshData
 *
 * \param 	None
 * \return 	None
 */
MeshData::~MeshData() {}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	None
 * \return 	None
 */
//void MeshData::draw() {}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	t   a time_t
 * \return 	None
 *
 */
/*void MeshData::draw(unsigned long long t) {

    glColor4d(0, 0, 1, 0.3);
    glBegin(GL_QUADS);
        glVertex3d(mesh->meshPos.getX()+100, mesh->meshPos.getY()+100, 0.0);
        glVertex3d(mesh->meshPos.getX()+100, mesh->meshPos.getY()+mesh->pdm-100, 0.0);
        glVertex3d(mesh->meshPos.getX()+mesh->pdm-100, mesh->meshPos.getY()+mesh->pdm-100, 0.0);
        glVertex3d(mesh->meshPos.getX()+mesh->pdm-100, mesh->meshPos.getY()+100, 0.0);
    glEnd();
}*/
