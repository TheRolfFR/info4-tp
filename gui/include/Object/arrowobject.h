#pragma once

#include <Object/object.h>
#include <Common/color.h>

#include <ogr_geometry.h>
#include <ogr_spatialref.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>

class ArrowObject : public ChildObject {
    private:
        OGRPoint m_view1;
        OGRPoint m_view2;
        OGRPoint m_modView1;
        OGRPoint m_modView2;

    public:
        ArrowObject();
        ~ArrowObject();

        virtual void draw(QMatrix4x4 &projection, QMatrix4x4 &view);
        virtual void draw(QMatrix4x4 &projection, QMatrix4x4 &view, unsigned long long t);
};
