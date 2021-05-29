#include <Object/tileobject.h>

#include <Common/utils2.h>

#include <ResourceManagement/datamanager.h>

#include <geologic-core/core/geologic-launcher/CoordinateSystemManager.h>

using std::cout;
using std::endl;

/**
 * \brief 	Default constructor of class TileObject
 *
 * \param 	None
 * \return 	None
 */
TileObject::TileObject(View* view, std::string layer, int x, int y, int zoom): ChildObject("TileObject")
{
    m_render_layer = view->addRenderObject(layer, this);
    m_x = x;
    m_y = y;
    m_zoom = zoom;

    /*
    int modX = x mod
    
    int size = 2 << m_zoom;
    //int max = size - 1;
    int grid_offset_x = m_x / size;

    OGRPoint data(x_max_wgs84, y_max_wgs84);
    CoordinateSystemManager* geoRefs = CoordinateSystemManager::getInstance();
    data1.assignSpatialReference(geoRefs->getDataRef());
    
    OGRPoint view4 = data4;
    view1.transformTo(geoRefs->getViewRef());

    view1.getX(), view1.getY(), -1,
        
    m_model.translate
    */
}


/**
 * \brief 	Default destructor of class TileObject
 *
 * \param 	None
 * \return 	None
 */
TileObject::~TileObject(){
}
