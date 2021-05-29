#ifndef BBOXDATA_H
#define BBOXDATA_H
#include <Data/data.h>
#include <geologic-core/objects/geo/untemporal/Bbox.h>

class BboxData : public Data
{
public:
    BboxData(Bbox* bbox);

    ~BboxData();

    Bbox * bbox;

    void draw();

    void draw(unsigned long long t);


};

#endif // BBOXDATA_H
