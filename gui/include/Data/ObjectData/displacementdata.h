#ifndef DISPLACEMENTDATA_H
#define DISPLACEMENTDATA_H

#include <Data/data.h>
#include <geologic-core/objects/dynamic/Displacement.h>



class DisplacementData : public Data {
public:

    Displacement * displacment;

    DisplacementData(Displacement * displacment);

    ~DisplacementData();

    void draw();

    void draw(unsigned long long t);


};


#endif // DISPLACEMENTDATA_H
