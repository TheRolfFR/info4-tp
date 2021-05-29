#ifndef TEMPORALGEOPOINTDATA_H
#define TEMPORALGEOPOINTDATA_H
#include <Data/data.h>
#include <memory>
#include <Common/color.h>
#include <geologic-core/objects/geo/temporal/TemporalGeoPoint.h>

class TemporalGeoPointData : public Data
{
public:
    TemporalGeoPointData(TemporalGeoPoint * tpgPoint);

    ~TemporalGeoPointData();

    TemporalGeoPoint * tpgPoint;

    void draw();

    void draw(unsigned long long t);


};

#endif // TEMPORALGEOPOINTDATA_H
