#include <Data/ObjectData/gridmeshdata.h>
#include <OpenGL/quaddisplayer.h>


/**
 * \brief 	Default constructor of class GridMeshData
 *
 * \param 	None
 * \return 	None
 */
GridMeshData::GridMeshData(GridMesh *gridmesh) : Data("GridMeshData")
{
    this->gridmesh = gridmesh;
}

/**
 * \brief 	Default destructor of class GridMeshData
 *
 * \param 	None
 * \return 	None
 */
GridMeshData::~GridMeshData() {

}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	None
 * \return 	None
 */
void GridMeshData::draw(){

}


/**
 * \brief 	Inherited method from class Data
 *
 * \param 	t   a time_t
 * \return 	None
 *
 */
void GridMeshData::draw(unsigned long long t) {
    Color c((rand()%100)/100.0, (rand()%100)/100.0, (rand()%100)/100.0, 1.0);

    OGRPoint* corner[4];
    OGRPoint BL = this->gridmesh->meshPos;
    corner[0] = &BL;

    OGRPoint BR = OGRPoint(BL.getX()+this->gridmesh->pdm, BL.getY(), 0.0);
    corner[1] = &BR;

    OGRPoint TR = OGRPoint(BL.getX()+this->gridmesh->pdm, BL.getY()+this->gridmesh->pdm, 0.0);
    corner[2] = &TR;

    OGRPoint TL = OGRPoint(BL.getX(), BL.getY()+this->gridmesh->pdm, 0.0);
    corner[3] = &TL;

    QuadDisplayer::drawQuad(corner, c);



}
