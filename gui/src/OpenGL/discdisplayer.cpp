#include <OpenGL/discdisplayer.h>
#include <QtOpenGL/QtOpenGL>
#include <cmath>
#include <geologic-core/core/geologic-launcher/CoordinateSystemManager.h>


DiscDisplayer::DiscDisplayer() {}

void DiscDisplayer::drawDiscFull(Color &fill_color, double radius, OGRPoint &center, OGRSpatialReference *view_reference) {
/*    const int slice_count = 40;
    // Convert center coordinates
    OGRPoint view_center = center;
    view_center.transformTo(view_reference);
    CoordinateSystemManager::getInstance();

    glColor4d(fill_color.red, fill_color.green, fill_color.blue, fill_color.alpha);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(view_center.getX(), view_center.getY(), view_center.getZ());
        for (int i=0; i<=slice_count; ++i) {
            glVertex3d(view_center.getX() + radius * cos(2.0 * i * M_PI / slice_count),
                       view_center.getY() + radius * sin(2.0 * i * M_PI / slice_count),
                       view_center.getZ());
        }
    glEnd();
}

void DiscDisplayer::drawDiscFullDirectly(Color &fill_color, double radius, OGRPoint &center) {
    const int slice_count = 40;
    OGRPoint view_center = center;

    glColor4d(fill_color.red, fill_color.green, fill_color.blue, fill_color.alpha);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(view_center.getX(), view_center.getY(), view_center.getZ());
        for (int i=0; i<=slice_count; ++i) {
            glVertex3d(view_center.getX() + radius * cos(2.0 * i * M_PI / slice_count),
                       view_center.getY() + radius * sin(2.0 * i * M_PI / slice_count),
                       view_center.getZ());
        }
    glEnd();

    */
}
