/**
 * \file	generatorobject.cpp
 * \class	GeneratorObject
 * \author	Nicolas Ballet (nicolas.ballet@utbm.fr)
 * \date	22/10/2018
 * \brief	GeneratorObject is a class representing a Generator
 */

#include <Object/generatorobject.h>

using namespace std;


/**
 * \brief 	Default constructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
GeneratorObject::GeneratorObject(View* view, std::string name):
    ParentObject(view, name),
    m_view(view)
{
}


/**
 * \brief 	Default destructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
GeneratorObject::~GeneratorObject() {
}


void GeneratorObject::update(QMatrix4x4& model, double t) {
    ParentObject::update(model, t);
    m_last_t = t;
    if(!m_hidden)
        ParentObject::update(m_proxy_model, t);
}
