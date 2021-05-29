#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <QString>
#include <string>

struct Config {
    Config() {}
    void load(const char *file);
    friend std::ostream &operator<<(std::ostream &os, const Config &me);

    bool loaded = false; ///< Boolean value to specify if the application is configured

    // Configuration variables
    bool proxy_enabled = false;
    QString proxy_address = "";
    unsigned short proxy_port = 1234;
    std::string tile_url_base = "http://a.tile.openstreetmap.org/%d/%d/%d.png";
    std::string overpass_url_base = "http://overpass-api.de/api/interpreter?data=";
    std::string data_epsg_code = "EPSG:4326";
    std::string view_epsg_code = "EPSG:2154";
    double x = 6.8;
    double y = 47.5;
    int zoom = 13;
};

#endif // CONFIG_H
