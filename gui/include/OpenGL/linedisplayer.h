#ifndef LINEDISPLAYER_H
#define LINEDISPLAYER_H

#include <ogr_geometry.h>
#include <ogr_spatialref.h>
#include <Common/color.h>

class LineDisplayer {
public:
    LineDisplayer() {}
    static void draw(const OGRLineString *line, Color *c, double width, OGRSpatialReference *to);
    static void drawDirectly(const OGRLineString *line, Color *c, double width);
    static void drawLineArrow(const OGRLineString *line, Color *c, double width, double length);
};

class MultiLineDisplayer {
public:
    MultiLineDisplayer() {}
    static void draw(const OGRMultiLineString *line, Color *c, double width, OGRSpatialReference *to);
    static void drawDirectly(const OGRMultiLineString *lines, Color *c, double width);
};

#endif // LINEDISPLAYER_H
