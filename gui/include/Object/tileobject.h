#pragma once

#include <Object/childobject.h>
#include <Common/color.h>

#include <ogr_geometry.h>
#include <ogr_spatialref.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>

class TileObject : public ChildObject {
    private:
        OGRPoint m_view1;
        OGRPoint m_view2;
        OGRPoint m_view3;
        OGRPoint m_view4;
        OGRPoint m_modView1;
        OGRPoint m_modView2;
        OGRPoint m_modView3;
        OGRPoint m_modView4;
        float m_points[8];

    public:
        TileObject(View* view, std::string layer, int x, int y, int zoom);
        ~TileObject();

        int m_zoom;
        int m_x;
        int m_y;
};
