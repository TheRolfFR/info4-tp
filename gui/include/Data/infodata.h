#ifndef INFODATA_H
#define INFODATA_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <Data/data.h>
#include <Common/color.h>
#include <Simulation/simulationclock.h>
#include <sys/time.h>
#include <iostream>
#include <ogr_geometry.h>
#include <OpenGL/quaddisplayer.h>
#include <OpenGL/multipointsdisplayer.h>


class infoData : public Data {

    private:
        std::string id;
        std::string string_time_begin;
        std::string string_time_end;
        std::string string_time_durant;
        std::string string_distance;

        void drawBackGround();

    public:
        infoData();
        ~infoData();

        void initInfo();
        void setInfo(int id, time_t t_begin, time_t t_end, double distance);
};

#endif // INFODATA_H
