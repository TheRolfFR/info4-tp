#include <Data/testdata.h>
#include <OpenGL/linedisplayer.h>
#include <OpenGL/quaddisplayer.h>
#include <OpenGL/discdisplayer.h>


testData::testData() : Data("testData") {

    std::vector<float> vertices = {
        -0.5, -0.5, 0,
        -0.5, 0.5, 0,
        0.5, -0.5, 0
    };

    setVertices(vertices);
}


testData::~testData() {

}

/*
void testData::draw() {

    OGRPoint* corner[4];
    OGRPoint BL = OGRPoint(-150.0, -250.0);
    corner[0] = &BL;

    OGRPoint BR = OGRPoint(200.0, -250.0);
    corner[1] = &BR;

    OGRPoint TR = OGRPoint(200.0, 200.0);
    corner[2] = &TR;

    OGRPoint TL = OGRPoint(-150.0, 200.0);
    corner[3] = &TL;

    //QuadDisplayer::drawQuad(corner, Color(1, 1, 1, 0.8));

    std::unique_ptr<OGRLinearRing> line = std::make_unique<OGRLinearRing>();

    OGRPoint point1 = OGRPoint(-65.0, 45.0, 0.0);
    line->addPoint(&point1);
    OGRPoint point2 = OGRPoint(35.0, 50, 0.0);
    line->addPoint(&point2);
    Color c(1.0,0.0,0.0,1.0);

    LineDisplayer::drawLineArrow(line.get(), &c, 2, 20);

    Color  origin(0.0,1.0,0.0,0.4);
    Color destination(1.0,0.0,0.0,0.4);
    DiscDisplayer::drawDiscFullDirectly(origin, 15, point1);
    DiscDisplayer::drawDiscFullDirectly(destination, 15, point2);



    glBegin(GL_LINE_STRIP);
    glColor4d(0.0,0.0,0.0,1.0);
    glPointSize(15);
    glVertex3d(-30.0, 45.0, 0.0);
    glVertex3d(-35.0, 50, 0.0);
    glVertex3d(-20.0, 70.0, 0.0);
    glVertex3d(-15.0, 32, 0.0);
    glVertex3d(0.0, 23, 0.0);
    glVertex3d(15, 10, 0.0);
    glVertex3d(75, 69, 0.0);
    glVertex3d(55, -10, 0.0);

    glEnd();

    std::unique_ptr<OGRLinearRing> templine = std::make_unique<OGRLinearRing>();
    templine->addPoint(-35.0, 50, 0.0);
    templine->addPoint(-30.0, 45.0, 0.0);
    templine->addPoint(-20.0, 70.0, 0.0);
    templine->addPoint(-15.0, 32, 0.0);
    templine->addPoint(0.0, 23, 0.0);
    templine->addPoint(15, 10, 0.0);
    templine->addPoint(55, -10, 0.0);
    templine->addPoint(75, 69, 0.0);
    //LineDisplayer::drawDirectly(templine.get(), &c, 5);


}


void testData::draw(unsigned long long simu_time) {

    this->draw();
}*/
