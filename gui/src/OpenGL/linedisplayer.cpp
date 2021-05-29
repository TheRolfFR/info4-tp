#include <OpenGL/linedisplayer.h>
#include <QtOpenGL/QtOpenGL>
#include <memory>
#include <iostream>
#include <math.h>
#include <OpenGL/arrowdisplayer.h>

using namespace std;

/*!
 * \brief LineDisplayer::draw draws a line after converting its coordinates
 * \param line the line as an OGRLineString
 * \param c the display color
 * \param width the line width
 * \param to the projected spatial reference
 */
void LineDisplayer::draw(const OGRLineString *line, Color *c, double width, OGRSpatialReference *to) {
/*    int count = line->getNumPoints();
    OGRSpatialReference *dataRef = line->getSpatialReference();
    if (dataRef == nullptr || to == nullptr || c == nullptr) {
        cerr << "LineDisplayer::draw: empty spatial reference" << endl;
        return;
    }
    auto xs = make_unique<double[]>(count);
    auto ys = make_unique<double[]>(count);
    for (int i=0; i<count; ++i) {
        OGRPoint tmp;
        line->getPoint(i, &tmp);
        xs.get()[i] = tmp.getX();
        ys.get()[i] = tmp.getY();
    }
    if (dataRef->IsSame(to) == 0) {
        OGRCoordinateTransformation *t = OGRCreateCoordinateTransformation(dataRef, to);
        if (t == nullptr)
            return;
        if (t->Transform(count, xs.get(), ys.get()) == 0)
            return;
    }
    glColor4d(c->red, c->green, c->blue, c->alpha);
    glLineWidth(static_cast<GLfloat>(width));
    glBegin(GL_LINE_STRIP);
        for (int i=0; i<count; ++i) {
            glVertex3d(xs.get()[i], ys.get()[i], 0.0);
        }
        glEnd();
        */
}

/*!
 * \brief LineDisplayer::drawDirectly draws a line without coordinates conversion
 * \param line the line as an OGRLineString
 * \param c the display color
 * \param width the line width
 */
void LineDisplayer::drawDirectly(const OGRLineString *line, Color *c, double width) {
    /*
    int count = line->getNumPoints();
    glColor4d(c->red, c->green, c->blue, c->alpha);
    glLineWidth(static_cast<GLfloat>(width));
    glBegin(GL_LINE_STRIP);
        for (int i=0; i<count; ++i) {
            OGRPoint tmp;
            line->getPoint(i, &tmp);
            glVertex3d(tmp.getX(), tmp.getY(), 0.0);
        }
    glEnd();


    */
}

/*!
 * \brief LineDisplayer::drawLineArrow draws a line with an arrow
 * \param line the line as an OGRLineString
 * \param c the display color
 * \param width the line width
 * \param length the arrow length
 */
void LineDisplayer::drawLineArrow(const OGRLineString *line, Color *c, double width, double length) {
    /*
    int count = line->getNumPoints();
    glColor4d(c->red, c->green, c->blue, c->alpha);
    glLineWidth(static_cast<GLfloat>(width));
    glBegin(GL_LINE_STRIP);
        for (int i=0; i<count; ++i) {
            OGRPoint tmp;
            line->getPoint(i, &tmp);
            glVertex3d(tmp.getX(), tmp.getY(), 0.0);
        }
    glEnd();
    //partie draw arrow

    ArrowDisplayer::drawArrow(line, c, width, length);


    */
}

/*!
 * \brief MultiLineDisplayer::draw draws a set of lines after converting its coordinates
 * \param lines the set of lines in an OGRMultiLineString
 * \param c the display color
 * \param width the line width
 * \param to the projected spatial reference
 */
void MultiLineDisplayer::draw(const OGRMultiLineString *lines, Color *c, double width, OGRSpatialReference *to) {
    /*
    int count = lines->getNumGeometries();
    OGRSpatialReference *dataRef = lines->getSpatialReference();
    if (dataRef == nullptr || to == nullptr)
        return;
    for (int i=0; i<count; ++i) {
        OGRLineString *line = (OGRLineString *) lines->getGeometryRef(i);
        line->assignSpatialReference(dataRef);
        LineDisplayer::draw(line, c, width, to);
    }
    */
}

/*!
 * \brief MultiLineDisplayer::drawDirectly draws a set of lines without converting its coordinates
 * \param lines the set of lines in an OGRMultiLineString
 * \param c the display color
 * \param width the line width
 */
void MultiLineDisplayer::drawDirectly(const OGRMultiLineString *lines, Color *c, double width) {
    /*
    int count = lines->getNumGeometries();
    for (int i=0; i<count; ++i) {
        OGRLineString *line = (OGRLineString *) lines->getGeometryRef(i);
        LineDisplayer::drawDirectly(line, c, width);
    }
    */
}
