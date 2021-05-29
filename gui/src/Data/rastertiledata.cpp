#include <Data/rastertiledata.h>

#include <Common/utils2.h>

#include <ogr_geometry.h>
#include <ogr_spatialref.h>
#include <geologic-core/core/geologic-launcher/CoordinateSystemManager.h>

/**
 * \brief 	Default constructor of class RasterTileData
 *
 * \param 	None
 * \return 	None
 */
RasterTileData::RasterTileData(int x, int y, int zoom): UniqueData("RasterTileData")
{
    double x_min = Utils::tile2utm(x, zoom);
    double y_min = Utils::tile2utm(y + 1, zoom);

    double x_max = Utils::tile2utm(x + 1, zoom);
    double y_max = Utils::tile2utm(y, zoom);

//    double min_utm = Utils::tile2utm(0, m_zoom);
//    double max_utm = Utils::tile2utm(max, m_zoom);

    double x_min_wgs84 = Utils::utm2lon(x_min);
    double y_min_wgs84 = Utils::utm2lat(y_min);

    double x_max_wgs84 = Utils::utm2lon(x_max);
    double y_max_wgs84 = Utils::utm2lat(y_max);
    
//    double min_wgs84 = Utils::tile2utm(min_utm, m_zoom);
//    double max_wgs84 = Utils::tile2utm(max_utm, m_zoom);

    OGRPoint data1(x_min_wgs84, y_min_wgs84);
    OGRPoint data2(x_max_wgs84, y_min_wgs84);
    OGRPoint data3(x_min_wgs84, y_max_wgs84);
    OGRPoint data4(x_max_wgs84, y_max_wgs84);
    CoordinateSystemManager* geoRefs = CoordinateSystemManager::getInstance();
    data1.assignSpatialReference(geoRefs->getDataRef());
    data2.assignSpatialReference(geoRefs->getDataRef());
    data3.assignSpatialReference(geoRefs->getDataRef());
    data4.assignSpatialReference(geoRefs->getDataRef());

    OGRPoint view1 = data1;
    OGRPoint view2 = data2;
    OGRPoint view3 = data3;
    OGRPoint view4 = data4;
    view1.transformTo(geoRefs->getViewRef());
    view2.transformTo(geoRefs->getViewRef());
    view3.transformTo(geoRefs->getViewRef());
    view4.transformTo(geoRefs->getViewRef());
    
    std::vector<float> vertices = {
        view1.getX(), view1.getY(), -1,
        view3.getX(), view3.getY(), -1,
        view2.getX(), view2.getY(), -1,
        view4.getX(), view4.getY(), -1,
    };

    std::vector<float> uvs = {
        0, 0,
        0, 1,
        1, 0,
        1, 1,
    };

    setVertices(vertices);
    setUVs(uvs);
    setStructureType(GL_TRIANGLE_STRIP);
}

/**
 * \brief 	Default destructor of class RasterTileData
 *
 * \param 	None
 * \return 	None
 */
RasterTileData::~RasterTileData(){}
