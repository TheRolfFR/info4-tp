#ifndef TRIPDATA_H
#define TRIPDATA_H
#include <Data/data.h>
#include <geologic-core/objects/dynamic/Trip.h>
#include <OpenGL/arrowdisplayer.h>


class tripData : public Data {
public:

    Trip *trip;

    tripData(Trip *trip);

    ~tripData();

    void draw();

    void draw(unsigned long long t);
};

#endif // TRIPDATA_H
