/**
 * \file	meshObject.h
 */
#pragma once

#include <Object/childobject.h>
#include <geologic-core/objects/geo/untemporal/GridMesh.h>

class MeshObject : public ChildObject {

    public:
        //*/ -------------------------------------------------
        MeshObject(std::shared_ptr<Shader> shader, GridMesh* mesh);
        virtual ~MeshObject();

        //*/ -------------------------------------------------
        GridMesh* mesh;
};
