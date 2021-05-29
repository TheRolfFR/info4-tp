#include "Scene/genericlayer.h"
#include <iostream>

#include <Object/childobject.h>
#include <layercheckbox.h>

using namespace std;

GenericLayer::GenericLayer(string &n, std::shared_ptr<Material> material, std::shared_ptr<Data> data): GenericLayer(n.c_str(), material, data){
}


GenericLayer::GenericLayer(const char* n, std::shared_ptr<Material> material, std::shared_ptr<Data> data): Layer(n),
    m_material(material),
    m_data(data)
{
}


GenericLayer::~GenericLayer() {
}


/*!
 * \brief Draws the childrens
 */
void GenericLayer::draw(QMatrix4x4 &projection, QMatrix4x4 &view) {
    if(!m_hidden) {
        m_shader->bind();
        m_shader->setUniformValue("projection", projection);
        m_shader->setUniformValue("view", view);

        // Real time for animations
        int time = QDateTime::currentMSecsSinceEpoch();
        m_shader->setUniformValue("time", time);
        m_material->bind(m_shader.get());
    
        m_data->bind();

        for(auto& c: m_childs) {
            c->draw(m_shader.get());
        }
    }
}
