#ifndef CLOCKDATA_H
#define CLOCKDATA_H

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <Data/data.h>
#include <Common/color.h>

#include <Simulation/simulationclock.h>
#include <sys/time.h>
#include <iostream>



class ClockData : public Data {

    public:

        ClockData();
        ~ClockData();

        void drawBackGround();

//        virtual void draw();
//        virtual void draw(unsigned long long t);

};

#endif // CLOCKDATA_H
