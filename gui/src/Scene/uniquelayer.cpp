#include "Scene/uniquelayer.h"
#include <iostream>

#include <Object/childobject.h>
#include <layercheckbox.h>

using namespace std;

UniqueLayer::UniqueLayer(string &n): UniqueLayer(n.c_str()){
}


UniqueLayer::UniqueLayer(const char* n): Layer(n){
}


UniqueLayer::~UniqueLayer() {
}


/*!
 * \brief Draws the childrens
 */
void UniqueLayer::draw(QMatrix4x4 &projection, QMatrix4x4 &view) {
    if(!m_hidden) {
        m_shader->bind();
        m_shader->setUniformValue("projection", projection);
        m_shader->setUniformValue("view", view);

        // Real time for animations
        int time = QDateTime::currentMSecsSinceEpoch();
        m_shader->setUniformValue("time", time);

        for(auto& c: m_childs) {
            c->draw(m_shader.get());
        }
    }
}
