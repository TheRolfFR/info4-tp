#include <Object/backgroundobject.h>

#include <ResourceManagement/datamanager.h>
#include <ResourceManagement/shadermanager.h>

using std::cout;
using std::endl;

/**
 * \brief 	Default constructor of class BackgroundObject
 *
 * \param 	None
 * \return 	None
 */
BackgroundObject::BackgroundObject(double r, double g, double b, double a): ChildObject("BackgroundObject")
{
    setData(DataManager::getInstance()->get("quad"));
    setMaterial(std::make_shared<Material>("background"));
    getMaterial()->setColor("diffuse", QVector4D(r, g, b, a));
    
    m_shader = ShaderManager::getInstance()->get("background");
}


/**
 * \brief 	Default destructor of class BackgroundObject
 *
 * \param 	None
 * \return 	None
 */
BackgroundObject::~BackgroundObject(){
}


void BackgroundObject::draw() {
    m_shader->bind();
    m_data->bind();
    ChildObject::draw(m_shader.get());
}
