#pragma once

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <Object/object.h>
#include <Common/color.h>

#include <Simulation/simulationclock.h>
#include <sys/time.h>
#include <iostream>


class ClockObject : public Object {

    public:

        ClockObject(std::shared_ptr<Shader> shader);
        ~ClockObject();

        void setCurrentSimuClock(SimulationClock* s_clock) ;
        void drawBackGround();

//        virtual void draw();
//        virtual void draw(unsigned long long t);

        SimulationClock* s_clock;
};
