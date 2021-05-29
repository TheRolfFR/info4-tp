#include <OpenGL/quaddisplayer.h>

QuadDisplayer::QuadDisplayer() {

}


void QuadDisplayer::draw(OGRPoint corners[4], const std::string &texture_file, OGRSpatialReference *to) {
    /*
    glColor4d(1.0, 1.0, 1.0, 0.8);

    glLineWidth(2.0);
    glBegin(GL_QUADS);

    for(unsigned int i=0; i<4; i++) {
        glVertex2d(corners[i].getX(), corners[i].getY());
    }

    glEnd();
    */
}


void QuadDisplayer::drawQuad(OGRPoint* corners[4]) {
    /*
    glColor4d(1.0,1.0,1.0,0.9);

    glLineWidth(2.0);
    glBegin(GL_QUADS);

    for(unsigned int i=0; i<4; i++) {
        glVertex2d(corners[i]->getX(), corners[i]->getY());
    }

    glEnd();
*/

}



void QuadDisplayer::drawQuad(OGRPoint *corners[], Color color) {
    /*
    glColor4d(color.red, color.blue, color.green, color.alpha);

    glLineWidth(2.0);
    glBegin(GL_QUADS);

    for(unsigned int i=0; i<4; i++) {
        glVertex2d(corners[i]->getX(), corners[i]->getY());
    }

    glEnd();
    */
}
