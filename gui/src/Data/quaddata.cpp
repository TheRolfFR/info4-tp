#include <Data/quaddata.h>

/**
 * \brief 	Default constructor of class QuadData
 *
 * \param 	None
 * \return 	None
 */
QuadData::QuadData(): GenericData("QuadData")
{
    std::vector<float> vertices = {
        -1, -1, 0,
        -1,  1, 0,
         1, -1, 0,
         1,  1, 0,
         1, -1, 0,
        -1,  1, 0,
    };
    
    std::vector<float> uvs = {
        0, 0,
        0, 1,
        1, 0,
        1, 1,
        1, 0,
        0, 1,
    };

    setUVs(uvs);
    setVertices(vertices);
    setStructureType(GL_TRIANGLES);
}

/**
 * \brief 	Default destructor of class QuadData
 *
 * \param 	None
 * \return 	None
 */
QuadData::~QuadData(){}
