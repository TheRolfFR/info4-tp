#ifndef ARROW3D_H
#define ARROW3D_H

#include <Data/data.h>
#include <Common/color.h>
#include <ogr_geometry.h>
#include <QtOpenGL/QtOpenGL>
#include <vector>
#include <memory>
#include <iostream>


class Arrow3D : public Data {
public:
    Arrow3D();
    ~Arrow3D();

    void draw(unsigned long long simu_time);
    void draw();


};

class Arrow3dDisplayer{
public:
    Arrow3dDisplayer();

    /*!
     * \brief draw an arrow in 3D
     * \param line line inclued two points
     */
    static void drawArrow3D(OGRMultiPoint* pointList);


};

#endif // ARROW3D_H
