#include <Object/areaobject.h>

#include <Common/utils2.h>

#include <ResourceManagement/datamanager.h>

using std::cout;
using std::endl;

/**
 * \brief 	Default constructor of class AreaObject
 *
 * \param 	None
 * \return 	None
 */
AreaObject::AreaObject(std::shared_ptr<Shader> shader): ChildObject(shader, "AreaObject")
{
    m_data = DataManager::getInstance()->get("point");
}


/**
 * \brief 	Default destructor of class AreaObject
 *
 * \param 	None
 * \return 	None
 */
AreaObject::~AreaObject(){
}
