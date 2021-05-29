#ifndef ZONEDISPLAYER_H
#define ZONEDISPLAYER_H

#include <QtOpenGL/QtOpenGL>
#include <ogr_geometry.h>
#include <Common/color.h>

class ZoneDisplayer {
public:
    ZoneDisplayer() {}

    /*!
     * \brief draw draws a filled polygon. To draw only the boundaries, use (Multi)LineDisplayer instead \see LineDisplayer.
     * \param border the geometry of the polygon, from first point to the last, last to first point line is drawed too.
     * \param c the fill color
     * \param to the projected coordinate system (to convert from data CS to view CS).
     */
    static void draw(const OGRLineString *border, Color *c, OGRSpatialReference *to);

    /*!
     * \brief draw draws all zones defined by border
     * \param border the geometry of the polygons, from first point to the last, last to first point line is drawed too.
     * \param c the fill color
     * \param to the projected coordinate system (to convert from data CS to view CS).
     */
    static void draw(const OGRMultiLineString *borders, Color *c, OGRSpatialReference *to);
};

#endif // ZONEDISPLAYER_H
