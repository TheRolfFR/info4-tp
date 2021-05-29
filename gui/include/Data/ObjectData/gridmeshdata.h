#ifndef MESHGRIDDATA_H
#define MESHGRIDDATA_H
#include <Data/data.h>
#include <geologic-core/objects/geo/untemporal/GridMesh.h>

class GridMeshData : public Data
{
public:
    GridMeshData(GridMesh * gridmesh);

    ~GridMeshData();

    GridMesh * gridmesh;

    void draw();

    void draw(unsigned long long t);

    void drawBaseGm(GridMesh * gm);

};

#endif // MESHGRIDDATA_H
