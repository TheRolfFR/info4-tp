#include "Object/parentobject.h"
#include <iostream>

#include <Scene/view.h>

using namespace std;

ParentObject::ParentObject(View* view, string &n): ParentObject(view, n.c_str()){
}


ParentObject::ParentObject(View*, const char* n): Object(n) {}


ParentObject::~ParentObject() {
	for(auto& c: m_childs) {
		delete c;
	}
	m_childs.clear();
}


void ParentObject::update(QMatrix4x4 &model, double t) {
    Object::update(model, t);
    for(auto& c: m_childs) {
        c->update(m_proxy_model, t);
    }
}


void ParentObject::removeChild(Object* obj) {
    m_childs.erase(find(m_childs.begin(), m_childs.end(), obj));
}
