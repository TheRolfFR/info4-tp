#ifndef GEOZONEDATA_H
#define GEOZONEDATA_H
#include <Data/data.h>
#include <geologic-core/objects/geo/untemporal/GeoZone.h>
#include <Data/ObjectData/bboxdata.h>

class GeoZoneData : public Data
{
public:
    GeoZoneData(GeoZone * geozone);

    ~GeoZoneData();

    GeoZone * geozone;

    void draw();

    void draw(unsigned long long t);

};

#endif // GEOZONEDATA_H
