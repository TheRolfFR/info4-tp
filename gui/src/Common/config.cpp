#include <Common/config.h>
#include <QXmlStreamReader>
#include <QXmlInputSource>
#include <QXmlStreamAttribute>
#include <QFile>
#include <QObject>
#include <iostream>

using namespace std;

void Config::load(const char *file) {
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QXmlStreamReader reader(&f);
    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType tok = reader.readNext();
        if (tok == QXmlStreamReader::StartElement) {
            if (reader.name().toString() == "datareference") {
                data_epsg_code = reader.attributes().value("refCode").toString().toStdString();
            } else if (reader.name().toString() == "viewreference") {
                view_epsg_code = reader.attributes().value("refCode").toString().toStdString();
            } else if (reader.name().toString() == "center") {
                x = reader.attributes().value("x").toDouble();
                y = reader.attributes().value("y").toDouble();
            } else if (reader.name().toString() == "osmtiles") {
                tile_url_base = reader.attributes().value("href").toString().toStdString();
                // TODO: add filter color
            } else if (reader.name().toString() == "overpass") {
                overpass_url_base = reader.attributes().value("href").toString().toStdString();
            } else if (reader.name().toString() == "proxy") {
                proxy_enabled = reader.attributes().value("enabled").toString() == "false" ? false: true;
                proxy_address = reader.attributes().value("host").toString();
                proxy_port = reader.attributes().value("port").toUShort();
            } else if (reader.name().toString() == "zoom") {
                zoom = reader.attributes().value("value").toInt();
            }
        }
    }
    loaded = true;
}

ostream &operator<<(ostream &os, const Config &me) {
    cout << "Proxy enabled: " << (me.proxy_enabled ? "true" : "false") << endl;
    cout << "Proxy address: " << me.proxy_address.toStdString() << endl;
    cout << "Proxy port: " << me.proxy_port << endl;
    cout << "Tiles URL: " << me.tile_url_base << endl;
    cout << "Overpass URL: " << me.overpass_url_base << endl;
    cout << "Data ref EPSG: " << me.data_epsg_code << endl;
    cout << "View ref EPSG: " << me.view_epsg_code << endl;
    cout << "Center: " << me.x << ", " << me.y << endl;
    cout << "Zoom: " << me.zoom << endl;
    return os;
}

