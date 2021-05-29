#include <OpenGL/multipointsdisplayer.h>
#include <QtOpenGL/QtOpenGL>
#include <iostream>
#include <memory>

using namespace std;

MultipointsDisplayer::MultipointsDisplayer() {}

void MultipointsDisplayer::draw(OGRMultiPoint *points, Color *c, double size, OGRSpatialReference *from, OGRSpatialReference *to) {
/*    if (points == nullptr)
        return;
    int count = points->getNumGeometries();
    auto xs = make_unique<double[]>(count);
    auto ys = make_unique<double[]>(count);
    for (int i=0; i<count; ++i) {
        OGRPoint *point = (OGRPoint *) points->getGeometryRef(i);
        xs.get()[i] = point->getX();
        ys.get()[i] = point->getY();
    }
    if (from->IsSame(to) == 0) {
        OGRCoordinateTransformation *t = OGRCreateCoordinateTransformation(from, to);
        if (t == nullptr) {
            cout << "Cannot create transform" << endl;
            return;
        }
        if (t->Transform(count, xs.get(), ys.get()) == 0) {
            cout << "Cannot use transform" << endl;
            return;
        }
    }
    glColor4d(c->red, c->green, c->blue, c->alpha);
    glPointSize(size);
    glBegin(GL_POINTS);
        for (int i=0; i<count; ++i)
            glVertex3d(xs.get()[i], ys.get()[i], 0.0);
    glEnd();
    */
}

void MultipointsDisplayer::drawDirectly(OGRMultiPoint *points, Color *c, double size)  {
    /*
    if (points == nullptr)
        return;
    int count = points->getNumGeometries();
    auto xs = make_unique<double[]>(count);
    auto ys = make_unique<double[]>(count);
    for (int i=0; i<count; ++i) {
        OGRPoint *point = (OGRPoint *) points->getGeometryRef(i);
        xs.get()[i] = point->getX();
        ys.get()[i] = point->getY();
    }

    glColor4d(c->red, c->green, c->blue, c->alpha);
    glPointSize(size);
    glBegin(GL_POINTS);
        for (int i=0; i<count; ++i)
            glVertex3d(xs.get()[i], ys.get()[i], 0.0);
    glEnd();
    */
}
