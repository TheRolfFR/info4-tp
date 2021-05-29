#include "Object/object.h"

#include <Scene/view.h>

Object::Object(std::string &name): Object(name.c_str()) {
}


Object::Object(const char* name):
    m_name(name),
    m_hidden(false) {
}


Object::~Object() {
}


void Object::update(QMatrix4x4& model, double) {
    if(!m_hidden)
        m_proxy_model = model * m_model;
}
