#include "Common/utils2.h"
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

auto Utils::OsmToWgs84(double x, double y)
{
    return make_tuple(Utils::utm2lon(x), Utils::utm2lat(y));
}

auto Utils::wgs84ToOsm(double lon, double lat)
{
    return make_tuple(Utils::long2utm(lon), Utils::lat2utm(lat));
}

auto Utils::wgs84ToOsm(const OGRPoint &p)
{
    return Utils::wgs84ToOsm(p.getX(), p.getY());
}

tuple<double, double, double, double> Utils::wgs84Bbox(const OGRPoint &p, int w, int h, const int zoom)
{
    double center_x, center_y;
    double alpha = 1.0 / (256.0 * pow(2.0, zoom));
    tie(center_x, center_y) = Utils::wgs84ToOsm(p);
    double view_x_min = center_x - w / 2.0 * alpha;
    double view_x_max = center_x + w / 2.0 * alpha;
    double view_y_min = 1.0 - (center_y + h / 2.0 * alpha);
    double view_y_max = 1.0 - (center_y - h / 2.0 * alpha);
    double wgs84_x_min, wgs84_x_max, wgs84_y_min, wgs84_y_max;
    tie(wgs84_x_min, wgs84_y_min) = Utils::OsmToWgs84(view_x_min, 1.0 - view_y_min);
    tie(wgs84_x_max, wgs84_y_max) = Utils::OsmToWgs84(view_x_max, 1.0 - view_y_max);
    //cout << wgs84_x_min << ", " << wgs84_y_min << ", " << wgs84_x_max << ", " << wgs84_y_max << endl;
    //Utils::message("Box: %lf, %lf, %lf, %lf\n", wgs84_x_min, wgs84_y_min, wgs84_x_max, wgs84_y_max);
    return make_tuple(wgs84_x_min, wgs84_y_min, wgs84_x_max, wgs84_y_max);
}

double Utils::long2utm(double lon) {
    return (lon + 180.0) / 360.0;
}

double Utils::lat2utm(double lat) {
    return (1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0;
}

double Utils::utm2lon(double utm_x) {
    return utm_x * 360.0 - 180.0;
}

double Utils::utm2lat(double utm_y) {
    double lat = atan(sinh(M_PI * (1.0 - 2.0 * utm_y)));
    return lat * 180.0 / M_PI;
}

int Utils::long2tilex(double lon, int z)
{
    return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
}

int Utils::lat2tiley(double lat, int z)
{
    return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z)));
}

int Utils::utm2tile(double utm, int zoom)
{
    return (int) floor(pow(2.0, zoom) * utm);
}

double Utils::tile2utm(int idx, int zoom)
{
    return (double) idx / pow(2.0, zoom);
}

void Utils::start(const char *func) {
#if 0
    string s = "";
    for (int i=0; i<level; ++i)
        s.append("| ");
    cout << s << "-> " << func << endl;
    ++level;
#endif
}

void Utils::end(const char *func) {
#if 0
    --level;
    string s = "";
    for (int i=0; i<level; ++i)
        s.append("| ");
    cout << s << "<- " << func << endl;
#endif
}

void Utils::message(const char *msg, ...) {
    string s = "";
    char buf[2048];
    for (int i=0; i<level; ++i)
        s.append("| ");
    s.append(" > ");
    va_list args;
    va_start(args, msg);
    sprintf(buf, "%s%s", s.c_str(), msg);
    printf(buf, args);
    va_end(args);
}

std::pair<double, double> Utils::seg_equation(const OGRPoint &p1, const OGRPoint &p2) {
    double a = (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
    double b = p1.getY() - a*p1.getX();
    return {a, b};
}

int Utils::level = 0;
