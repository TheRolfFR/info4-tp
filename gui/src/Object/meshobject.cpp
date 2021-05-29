/**
 * \file	meshObject.cpp
 * \class	VehiclePosition
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	01/01/2018
 * \brief	meshObject is a class representing a meshObject
 */

#include <Object/meshobject.h>

#include <ResourceManagement/datamanager.h>

using namespace std;


/**
 * \brief 	Default constructor of class MeshObject
 *
 * \param 	None
 * \return 	None
 */
MeshObject::MeshObject(std::shared_ptr<Shader> shader, GridMesh* mesh) : ChildObject(shader, "Mesh Object") {
    this->mesh = mesh;

    m_data = DataManager::getInstance()->get("default");
}

/**
 * \brief 	Default destructor of class MeshObject
 *
 * \param 	None
 * \return 	None
 */
MeshObject::~MeshObject() {}

/**
 * \brief 	Inherited method from class Object
 *
 * \param 	None
 * \return 	None
 */
//void MeshObject::draw() {}

/**
 * \brief 	Inherited method from class Object
 *
 * \param 	t   a time_t
 * \return 	None
 *
 */
/*void MeshObject::draw(unsigned long long t) {

    glColor4d(0, 0, 1, 0.3);
    glBegin(GL_QUADS);
        glVertex3d(mesh->meshPos.getX()+100, mesh->meshPos.getY()+100, 0.0);
        glVertex3d(mesh->meshPos.getX()+100, mesh->meshPos.getY()+mesh->pdm-100, 0.0);
        glVertex3d(mesh->meshPos.getX()+mesh->pdm-100, mesh->meshPos.getY()+mesh->pdm-100, 0.0);
        glVertex3d(mesh->meshPos.getX()+mesh->pdm-100, mesh->meshPos.getY()+100, 0.0);
    glEnd();
}*/
