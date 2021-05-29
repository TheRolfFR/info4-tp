#include "Object/childobject.h"
#include <iostream>
#include <Scene/layer.h>

using namespace std;

ChildObject::ChildObject(string &n): ChildObject(n.c_str()) {
}


ChildObject::ChildObject(const char* n):
    Object(n) {
}


ChildObject::~ChildObject() {
    if(m_render_layer)
        m_render_layer->removeChild(this);
}

/*!
 * \brief Draws the object itself if it has data and a material, then calls a draw for the children
 */
void ChildObject::draw(Shader* shader) {
    if (!shader)
        return;

    if(!m_hidden) {
        shader->setUniformValue("model", m_proxy_model);

        if(m_material)
            m_material->bind(shader);
        
        if (m_data)
            m_data->draw();
    }
}
