#include <OpenGL/arrowdisplayer.h>

ArrowDisplayer::ArrowDisplayer(){

}


void ArrowDisplayer::drawArrow(const OGRLineString *line, Color *c, double width, double length) {
/*
    OGRPoint pointOrigin;
    OGRPoint pointDestination;
    line->getPoint(0, &pointOrigin);
    line->getPoint(1, &pointDestination);

    // Find the arrow shaft unit vector.
    double vx = pointDestination.getX() - pointOrigin.getX() ;
    double vy = pointDestination.getY() - pointOrigin.getY() ;
    //double vz = pointDestination.getZ() - pointOrigin.getZ() ;

    float dist = (float)sqrt(vx * vx + vy * vy);
    double dx = vx/dist;
    double dy = vy/dist;

    float ax = length * (-dy - dx);
    float ay = length * (dx - dy);

    glColor4d(c->red, c->green, c->blue, c->alpha);
    glLineWidth(static_cast<GLfloat>(width));
    //glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glVertex3d(pointDestination.getX(), pointDestination.getY(), pointDestination.getZ());
    glVertex3d(pointDestination.getX() + ax, pointDestination.getY() + ay, 0.0);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex3d(pointDestination.getX(), pointDestination.getY(), pointDestination.getZ());
    glVertex3d(pointDestination.getX()- ay,pointDestination.getY() + ax, 0.0);
    glEnd();



    */
}
