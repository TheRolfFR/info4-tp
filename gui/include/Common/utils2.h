#ifndef UTILS_H
#define UTILS_H

#include <cstdarg>
#include <tuple>
#include <ogr_geometry.h>
#include <vector>
#include <iostream>

class Utils
{
public:
    static int level;

    /*!
     * \brief wgs84Bbox computes the wgs84 bounding box from a center, a zoom and screen size.
     * \param p the center of the screen, in wgs84
     * \param w the screen width in pixels
     * \param h the screen height in pixels
     * \param zoom the zoom as defined in well known tile servers
     */
    static std::tuple<double, double, double, double> wgs84Bbox(const OGRPoint &p, int w, int h, int zoom);

    /*!
     * \brief OsmToWgs84 converts normalized pseudo UTM to WGS84 coordinates
     * \param x the [0..1] longitude (from left to right)
     * \param y the [0..1] latitude (from top to bottom)
     */
    static auto OsmToWgs84(double x, double y);

    /*!
     * \brief conversion from WGS84 coordinates to [0,1.0]^2 pseudo UTM value
     * \param p WGS84 location (degree)
     * \return pseudo UTM value
     */
    static auto wgs84ToOsm(double lon, double lat);

    /*!
     * \brief conversion from WGS84 coordinates to [0,1.0]^2 pseudo UTM value
     * \param p WGS84 location (degree)
     * \return pseudo UTM value
     */
    static auto wgs84ToOsm(const OGRPoint &p);

    /*!
     * \brief conversion from WGS84 longitude to [0,1.0] pseudo UTM value
     * \param lon WGS84 longitude in degree
     * \return pseudo UTM value between 0 (180.0 °W) to 1.0 (180.0 °E)
     */
    static double long2utm(double lon);

    /*!
     * \brief conversion from WGS84 latitude to [0,1.0] pseudo UTM value
     * \param lat WGS84 latitude in degree
     * \return pseudo UTM value between 0 (i.e. 85.0511 °N) to 1.0 (i.e. 85.0511 °S)
     */
    static double lat2utm(double lat);

    /*!
     * \brief conversion from pseudo UTM x value to WGS84 longitude
     * \param utm_x pseudo UTM x value
     * \return WGS84 longitude value in degree
     */
    static double utm2lon(double utm_x);

    /*!
     * \brief conversion from pseudo UTM y value to WGS84 latitude
     * \param utm_y pseudo UTM y value
     * \return WGS84 latitude value in degree
     */
    static double utm2lat(double utm_y);

    /*!
     * \brief conversion from WGS84 longitude to tile x index
     * \param lon WGS84 longitude in degree
     * \param z zoom level (0 to 18)
     * \return x index of the bounding tile
     */
    static int long2tilex(double lon, int z);

    /*!
     * \brief conversion from WGS84 latitude to tile y index
     * \param lat WGS84 latitude in degree
     * \param z zoom level (0 to 18)
     * \return y index of the bounding tile
     */
    static int lat2tiley(double lat, int z);

    /*!
     * \brief utm2tile computes tile index based on its pseudo UTM coordinates
     * \param utm pseudo UTM
     * \param zoom, the zoom level
     * \return index
     */
    static int utm2tile(double utm, int zoom);

    /*!
     * \brief tile2utm converts from tile index to pseudo UTM coordinates
     * \param idx the tile index
     * \param zoom the zoom level
     * \return the pseudo UTM coordinate
     */
    static double tile2utm(int idx, int zoom);

    static void start(const char *func);
    static void end(const char *func);
    static void message(const char *msg, ...);

    /*!
     * \brief seg_equation returns the segment affine equation y=ax+b
     * \param p1 first point of the segment
     * \param p2 second point of the segment
     * \return a pair of double whose .first=a and .second=b
     */
    static std::pair<double, double> seg_equation(const OGRPoint &p1, const OGRPoint &p2) noexcept(false);
};

#endif // UTILS_H
