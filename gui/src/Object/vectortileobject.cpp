#include <Object/vectortileobject.h>

#include <Common/utils2.h>

#include <Material/vectortilematerial.h>
#include <ResourceManagement/vectortiledatamanager.h>
#include <ResourceManagement/framebuffermanager.h>

using std::cout;
using std::endl;

/**
 * \brief 	Default constructor of class VectorTileObject
 *
 * \param 	None
 * \return 	None
 */
VectorTileObject::VectorTileObject(View* view, int x, int y, int zoom): TileObject(view, "vector tile", x, y, zoom)
{
    m_material = std::make_unique<VectorTileMaterial>();
    m_data = VectorTileDataManager::getInstance()->importFromURL(x, y, zoom);
}


/**
 * \brief 	Default destructor of class VectorTileObject
 *
 * \param 	None
 * \return 	None
 */
VectorTileObject::~VectorTileObject(){
}
