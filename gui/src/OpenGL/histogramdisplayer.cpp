#include <OpenGL/histogramdisplayer.h>

using namespace std;

void HistogramDisplayer::draw(pair<double, double> x_bound, pair<double, double> y_bound, pair<double, double> z_bound, Color *c, Color *boundary) {
/*    if (c == nullptr)
        return;
    double x_min = get<0>(x_bound), x_max = get<1>(x_bound);
    double y_min = get<0>(y_bound), y_max = get<1>(y_bound);
    double z_min = get<0>(z_bound), z_max = get<1>(z_bound);
    glColor4d(c->red, c->green, c->blue, c->alpha);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3d(x_min, y_max, z_min); glVertex3d(x_min, y_min, z_min); glVertex3d(x_max, y_max, z_min); glVertex3d(x_max, y_min, z_min);
        glVertex3d(x_max, y_max, z_max); glVertex3d(x_max, y_min, z_max);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3d(x_max, y_min, z_max); glVertex3d(x_max, y_max, z_max); glVertex3d(x_min, y_min, z_max); glVertex3d(x_min, y_max, z_max);
        glVertex3d(x_min, y_min, z_min); glVertex3d(x_min, y_max, z_min);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3d(x_min, y_min, z_max); glVertex3d(x_min, y_min, z_min); glVertex3d(x_max, y_min, z_max); glVertex3d(x_max, y_min, z_min);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3d(x_min, y_max, z_max); glVertex3d(x_min, y_max, z_min); glVertex3d(x_max, y_max, z_max); glVertex3d(x_max, y_max, z_min);
    glEnd();
    if (boundary != nullptr) {
        glLineWidth(1.0);
        glColor4d(boundary->red, boundary->green, boundary->blue, boundary->alpha);
        glBegin(GL_LINE_LOOP);
            glVertex3d(x_min, y_min, z_min); glVertex3d(x_max, y_min, z_min); glVertex3d(x_max, y_max, z_min); glVertex3d(x_min, y_max, z_min);
        glEnd();
        glBegin(GL_LINE_LOOP);
            glVertex3d(x_min, y_min, z_max); glVertex3d(x_max, y_min, z_max); glVertex3d(x_max, y_max, z_max); glVertex3d(x_min, y_max, z_max);
        glEnd();
        glBegin(GL_LINE_LOOP);
            glVertex3d(x_min, y_min, z_min); glVertex3d(x_max, y_min, z_min); glVertex3d(x_max, y_min, z_max); glVertex3d(x_min, y_min, z_max);
        glEnd();
        glBegin(GL_LINE_LOOP);
            glVertex3d(x_min, y_min, z_min); glVertex3d(x_min, y_max, z_max); glVertex3d(x_max, y_max, z_max); glVertex3d(x_max, y_max, z_min);
        glEnd();
        glBegin(GL_LINE_LOOP);
            glVertex3d(x_min, y_max, z_min); glVertex3d(x_min, y_min, z_min); glVertex3d(x_min, y_min, z_max); glVertex3d(x_min, y_max, z_max);
        glEnd();
        glBegin(GL_LINE_LOOP);
            glVertex3d(x_max, y_max, z_min); glVertex3d(x_max, y_max, z_max); glVertex3d(x_max, y_min, z_max); glVertex3d(x_max, y_min, z_min);
        glEnd();
    }
    */
}
