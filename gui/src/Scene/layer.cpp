#include "Scene/layer.h"
#include <iostream>

#include <Object/childobject.h>
#include <layercheckbox.h>

using namespace std;

Layer::Layer(string &n): Layer(n.c_str()){
}


Layer::Layer(const char* n):
    m_name(n),
    m_hidden(false)
{
    m_shader = std::make_shared<Shader>(n);
    m_shader->load();
}


Layer::~Layer() {
}


void Layer::drawCheckbox(QWidget* tab, QLayout* layout) {
    if (layout != nullptr) {
        auto my_checkbox = new LayerCheckBox(this, QObject::tr(m_name.c_str()), tab);
        layout->addWidget(my_checkbox);
    }
}


void Layer::removeChild(ChildObject* obj) {
    m_childs.erase(find(m_childs.begin(), m_childs.end(), obj));
}
