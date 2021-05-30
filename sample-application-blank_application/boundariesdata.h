#ifndef BOUNDARIESDATA_H
#define BOUNDARIESDATA_H

#include "Data/uniquedata.h"
#include "osmloader.h"

class BoundariesData : public UniqueData
{
public:
    BoundariesData();
    void draw() {

    }
private:
    OSMLoader loader;
};

#endif // BOUNDARIESDATA_H
