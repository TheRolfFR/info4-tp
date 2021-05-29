#ifndef DISCDISPLAYER_H
#define DISCDISPLAYER_H

#include <Common/color.h>
#include <ogr_geometry.h>
#include <ogr_spatialref.h>

class DiscDisplayer {
public:
    DiscDisplayer();

    /*!
     * \brief draws a disc filled with color
     * \param fill_color the disc filled color
     * \param radius the disc radius
     * \param center the center of the disc, must have a pointer to DATA coordinates reference
     * \param view_reference a non-owning pointer to the VIEW coordinates reference
     */
    static void drawDiscFull(Color &fill_color, double radius, OGRPoint &center, OGRSpatialReference *view_reference);
    static void drawDiscFullDirectly(Color &fill_color, double radius, OGRPoint &center);
};

#endif // DISCDISPLAYER_H
