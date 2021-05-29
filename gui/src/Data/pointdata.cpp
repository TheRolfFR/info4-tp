#include <Data/pointdata.h>

/**
 * \brief 	Default constructor of class PointData
 *
 * \param 	None
 * \return 	None
 */
PointData::PointData(): GenericData("PointData")
{
    std::vector<float> vertices = {
        0, 0, 0,
    };

    setVertices(vertices);
    setStructureType(GL_POINTS);
}

/**
 * \brief 	Default destructor of class PointData
 *
 * \param 	None
 * \return 	None
 */
PointData::~PointData(){}
