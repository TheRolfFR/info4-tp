#ifndef MULTIPOINTSDISPLAYER_H
#define MULTIPOINTSDISPLAYER_H

#include <ogr_geometry.h>
#include <Common/color.h>

class MultipointsDisplayer {
public:
    MultipointsDisplayer();

    /*!
     * \brief draw draws a multipoints object (based on OGRMultiPoint class)
     * Does nothing if either one of these assertion is true: points is null,
     * a transform from *from to *to cannot be instanciated, or the
     * transform from *from to *to fails.
     * \param points the multipoints structure
     * \param c the color of the points
     * \param size the size of the points
     * \param from the spatial reference of the points provided
     * \param to the spatial reference of the display panel
     */
    static void draw(OGRMultiPoint *points, Color *c, double size, OGRSpatialReference *from, OGRSpatialReference *to);
    static void drawDirectly(OGRMultiPoint *points, Color *c, double size);
};

#endif // MULTIPOINTSDISPLAYER_H
