#include <Data/linedata.h>

/**
 * \brief 	Default constructor of class LineData
 *
 * \param 	None
 * \return 	None
 */
LineData::LineData(): GenericData("LineData")
{
    std::vector<float> vertices = {
        0, -0.5, 0,
        0,  0.5, 0,
        1, -0.5, 0,
        1, -0.5, 0,
        0,  0.5, 0,
        1,  0.5, 0,
    };
    
    std::vector<float> uvs = {
        0, 0,
        0, 1,
        1, 0,
        1, 0,
        0, 1,
        1, 1,
    };

    setUVs(uvs);
    setVertices(vertices);
    setStructureType(GL_TRIANGLES);
}

/**
 * \brief 	Default destructor of class LineData
 *
 * \param 	None
 * \return 	None
 */
LineData::~LineData(){}
