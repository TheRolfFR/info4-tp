#ifndef HISTOGRAMDISPLAYER_H
#define HISTOGRAMDISPLAYER_H

#include <QtOpenGL/QtOpenGL>
#include <utility>
#include <Common/color.h>

class HistogramDisplayer {
public:
    HistogramDisplayer() {}

    /*!
     * \brief draw draws a box (as an histogram bean)
     * \param x_bound the x min and max values, in view coordinate system
     * \param y_bound the y min and max values, in view coordinate system
     * \param z_bound the z min and max values, in view coordinate system
     * \param c the color to draw the bean (better has some transparency, but not mandatory)
     * \param boundary the color of the histogram bean boundaries. Not displayed if nullptr.
     */
    static void draw(std::pair<double, double> x_bound, std::pair<double, double> y_bound, std::pair<double, double> z_bound, Color *c, Color *boundary = nullptr);
};

#endif // HISTOGRAMDISPLAYER_H
