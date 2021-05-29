/**
 * \file	rootobject.h
 */
#pragma once

#include <Object/parentobject.h>

class RootObject : public ParentObject{
public:
    //*/ -------------------------------------------------
    RootObject(View* view);
    virtual ~RootObject();
    
    virtual void update(double t);

};
