#include <OpenGL/zonedisplayer.h>
#include <memory>
#include <array>
#include <iostream>
#include <cstdio>
#include <random>

#include <GL/glu.h>

using namespace std;

#ifndef CALLBACK
#define CALLBACK
#endif

void CALLBACK beginCB(GLenum type) {
//    glBegin(type);
//    cout << "Type: " << type << endl;
}

void CALLBACK vertexCB(void *vertex_data) {
    /*
    const GLdouble *pt = (const GLdouble *) vertex_data;
    glVertex3d(pt[0], pt[1], pt[2]);
    //cout << pt[0] << ", " << pt[1] << ", " << pt[2] << endl;
//    printf("%10.2lf %10.2lf %10.2lf\n", pt[0], pt[1], pt[2]);
    fflush(stdout);
    */
}

void CALLBACK endCB() {
//    cout << "glEnd()" << endl;
    //glEnd();
}

void CALLBACK combineCB(GLdouble coords[3], GLdouble *d[4], GLfloat w[4], void **dataOut) {
    /*
    array<GLdouble, 7> *v = new array<GLdouble, 7>();

    v[0][0] = coords[0];
    v[0][1] = coords[1];
    v[0][2] = coords[2];
    v[0][3] = d[0][0];
    v[0][4] = d[0][1];
    v[0][5] = d[0][2];
    v[0][6] = d[0][3];
//    cout << d[0][0] << ", " << d[0][1] << ", " << d[0][2] << ", " << d[0][3] << endl;
    *dataOut = v;
    */
}

void CALLBACK errorCB(GLenum errno) {
}

void ZoneDisplayer::draw(const OGRLineString *border, Color *c, OGRSpatialReference *to) {

    /*
    if (border == nullptr || c == nullptr || to == nullptr)
        return;
    int count = border->getNumPoints();

    OGRSpatialReference *dataRef = border->getSpatialReference();
    if (dataRef == nullptr || to == nullptr)
        return;

    auto xs = make_unique<double[]>(count);
    auto ys = make_unique<double[]>(count);

    for (int i=0; i<count; ++i) {
        OGRPoint tmp;
        border->getPoint(i, &tmp);
        xs.get()[i] = tmp.getX();
        ys.get()[i] = tmp.getY();
    }

    OGRCoordinateTransformation *t = OGRCreateCoordinateTransformation(dataRef, to);
    if (t == nullptr)
        return;
    if (t->Transform(count, xs.get(), ys.get()) == 0)
        return;

    auto coords = make_unique<double[]>(3*count);
    for (int i=0; i<count; ++i) {
        coords[3*i] = xs.get()[i];
        coords[3*i+1] = ys.get()[i];
        coords[3*i+2] = 0.0;
    }

    GLUtesselator *tess = gluNewTess();
    gluTessCallback(tess, GLU_TESS_BEGIN,   (void (CALLBACK *)())&beginCB);
    gluTessCallback(tess, GLU_TESS_END,     (void (CALLBACK *)())&endCB);
    gluTessCallback(tess, GLU_TESS_VERTEX,  (void (CALLBACK *)())&vertexCB);
    gluTessCallback(tess, GLU_TESS_COMBINE, (void (CALLBACK *)())&combineCB);
    gluTessCallback(tess, GLU_TESS_ERROR,   (void (CALLBACK *)())&errorCB);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);

    //glColor4d(dist(gen), dist(gen), dist(gen), 0.5);
    glColor4d(c->red, c->green, c->blue, 0.8);
    //cout << c->red << ", " << c->green << ", " << c->blue << ", " << c->alpha << endl;
    gluTessBeginPolygon(tess, NULL);
        gluTessBeginContour(tess);
        for (int i=count-1; i>=0; --i) {
            gluTessVertex(tess, &coords[3*i], &coords[3*i]);
        }
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    gluDeleteTess(tess);
    */
}

void ZoneDisplayer::draw(const OGRMultiLineString *borders, Color *c, OGRSpatialReference *to) {
    /*
    if (borders == nullptr || c == nullptr || to == nullptr)
        return;
    int count = borders->getNumGeometries();
    for (int i=0; i<count; ++i) {
        OGRLineString *line = (OGRLineString *) borders->getGeometryRef(i);
        line->assignSpatialReference(borders->getSpatialReference());
        draw(line, c, to);
    }
    */
}

