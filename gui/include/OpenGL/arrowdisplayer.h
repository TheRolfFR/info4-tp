#ifndef ARROWDISPLAYER_H
#define ARROWDISPLAYER_H

#include <Common/color.h>
#include <ogr_geometry.h>
#include <OpenGL/linedisplayer.h>
#include <QtOpenGL/QtOpenGL>


class ArrowDisplayer {
public:
    ArrowDisplayer();


    /*!
     * \brief draw an arrow head
     * \param line line inclued two points
     * \param c the fill color
     * \param width the forme of the arrow
     * \param length the length of the arrow
     */
    static void drawArrow(const OGRLineString *line, Color *c, double width, double length);

};

#endif // ARROWDISPLAYER_H
