/**
 * \file	rootobject.cpp
 * \class	RootObject
 * \author	Nicolas Ballet (nicolas.ballet@utbm.fr)
 * \brief	RootObject is a class representing a the tree's root
 */

#include <Object/rootobject.h>
#include <iostream>

using namespace std;


/**
 * \brief 	Default constructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
RootObject::RootObject(View* view):
    ParentObject(view, "Root")
{
}


/**
 * \brief 	Default destructor of class Vehicule
 *
 * \param 	None
 * \return 	None
 */
RootObject::~RootObject() {}


void RootObject::update(double t) {
//    cout << "Tree update" << endl;
    QMatrix4x4 model;
    ParentObject::update(model, t);
}
