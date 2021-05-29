#include <OpenGL/arrow3ddisplayer.h>
#include <OpenGL/quaddisplayer.h>
#include <OpenGL/linedisplayer.h>
#include <math.h>


Arrow3D::Arrow3D() : Data("Arrow3D") {

}


Arrow3D::~Arrow3D() {

}


void Arrow3D::draw(unsigned long long simu_time) {

}

//show the arrow in the screan
void Arrow3D::draw() {

/*
    //draw the background
    OGRPoint* corner[4];
    OGRPoint BL = OGRPoint(-150.0, -250.0);
    corner[0] = &BL;

    OGRPoint BR = OGRPoint(200.0, -250.0);
    corner[1] = &BR;

    OGRPoint TR = OGRPoint(200.0, 200.0);
    corner[2] = &TR;

    OGRPoint TL = OGRPoint(-150.0, 200.0);
    corner[3] = &TL;

    QuadDisplayer::drawQuad(corner, Color(0, 0, 0, 1.0));


    //draw the arrow


    std::unique_ptr<OGRMultiPoint> points = std::make_unique<OGRMultiPoint>();//points necessary


    OGRPoint point1(45,79.0,0.0);
    points->addGeometry(&point1);

    OGRPoint point2(-25.0,37.0,0.0);
    points->addGeometry(&point2);

    OGRPoint point3(50.0,15.0,0.0);
    points->addGeometry(&point3);


    OGRPoint point4(-15,-63,0.0);
    points->addGeometry(&point4);

    OGRPoint point5(36,-60,0.0);
    points->addGeometry(&point5);


    OGRPoint point6(69,80,0.0);
    points->addGeometry(&point6);

    OGRPoint point7(-66,-15,0.0);
    points->addGeometry(&point7);


    OGRPoint point8(50,-60,0.0);
    points->addGeometry(&point8);

    //this->drawArrowList(points.get());
    //this->drawArrow3D(points.get());

    Arrow3dDisplayer::drawArrow3D(points.get());

    int count = points->getNumGeometries();

    glBegin(GL_LINE_STRIP);
    glPointSize(5.0);
    glColor4d(1.0,0.0,0.0,0.45);

    for (int i=0; i< count; ++i) {
        OGRPoint *point_temp = (OGRPoint *) points->getGeometryRef(i);
        glVertex3d(point_temp->getX(),point_temp->getY(), point_temp->getZ());
    }


    glEnd();

    //Color c(0.45,0.45,0.45,0.45);
*/

}

/*!
 * \brief draw an arrow in 3D
 * \param line line inclued two points
 */
void Arrow3dDisplayer::drawArrow3D(OGRMultiPoint *pointList) {


    ///define the index necessary to draw the arrow
            /// from point_origin to point_destination
            /// --centre:: the center of the two points
            /// --radius:: distance of the two points / 2.0
            /// //radius default is 15 (can be modofied if necessary)
            /// --height:: thickness of the arrow (can be modified by user)
            /// --angle:: calcule arrording to the two points
            /// --index_angle:: index of rotating
            /// //+1 the next point is in the clockwise direction of the line, the arrow turn in the Counterclockwise direction, glRotated(+angle)
            /// //-1 the next point is in the Counterclockwise direction of the line, the arrow turn in the clockwise direction, glRotated(-angle)
            /// --color :: color of the arrow (can be modified by user)

/*
    //radius fixed
    double radius = 15.0;

    //height
    double height = 1.0;


    //length default = 30, centre default = 0.0,0.0,0.0
    float num_segments = 20.0 * sqrtf(radius);
    float theta = 2*M_PI / num_segments;
    float co = cosf(theta);//precalculate the sine and cosine
    float si = sinf(theta);
    float t;

    float y = radius;//we start at angle = 0
    float z = 0;

    //color of the arrow (can be modofied by user)
    Color color(1.0,0.0,0.0,0.0);


    ///Part of drawing the arrow in the glList
    ///
    ///
    //Add the points to the lists for drawing the arrow

    std::unique_ptr<OGRMultiPoint> points = std::make_unique<OGRMultiPoint>();//points necessary to draw the arrow

    double dx=0.0;


    for (int ii=0; ii< (num_segments*5/12.0); ii++) {

        std::unique_ptr<OGRPoint> point_temp = std::make_unique<OGRPoint>();

        if(ii > num_segments / 12.0) {
            double index_temp = (num_segments*5/12.0)*4/5.0 ;
            if(  ii < (index_temp-1) ){
                dx = dx + (1/(index_temp-1));

                point_temp->setX(dx);
                point_temp->setY(y);
                point_temp->setZ(z-radius/2.0);

                points->addGeometry(point_temp.get());


            } else if (ii <= index_temp){
                dx = dx + 2;
                point_temp->setX(dx);

                point_temp->setY(y);
                point_temp->setZ(z-radius/2.0);

                points->addGeometry(point_temp.get());



            } else {
                double unit = (dx / (num_segments*5/12.0 - ii + 1));
                dx = dx - unit;
                point_temp->setX(dx);

                point_temp->setY(y);
                point_temp->setZ(z-radius/2.0);

                points->addGeometry(point_temp.get());


            }
        }
        t = y;
        y = co*y - si*z;
        z = si*t + co*z;


    }


    //creat the glList
    GLuint index = glGenLists(1);


    //create the arrow  in 3d i the list
    glNewList(index, GL_COMPILE);


    int count = points->getNumGeometries();

    //top list

    glColor4d(color.red,color.green,color.blue,0.8);
    glTranslated(0.0,0.0,height/2.0);
    glPointSize(2.0);
    //glBegin(GL_POINTS);
    glBegin(GL_TRIANGLE_STRIP);
    //glVertex3d(10.0,0.0,0.0);
    for (int ii=0; ii<count; ++ii) {
        OGRPoint *point = (OGRPoint *) points->getGeometryRef(ii);
        glVertex3d(point->getX(), point->getY(), point->getZ());
        glVertex3d(-point->getX(), point->getY(), point->getZ());
    }
    glEnd();

    //two side list


    //the right side
    glTranslated(0.0,0.0,-height/2.0);
    glColor4d(color.red,color.green,color.blue,0.4);
    //glBegin(GL_POINTS);
    glBegin(GL_TRIANGLE_STRIP);
    //glVertex3d(0.0,0.0,0.0);
    for (int ii=0; ii<count; ++ii) {
        OGRPoint *point = (OGRPoint *) points->getGeometryRef(ii);
        glVertex3d(point->getX(), point->getY(), point->getZ() - (height/2));
        glVertex3d(point->getX(), point->getY(), point->getZ() + (height/2));

    }
    glEnd();


    //the left side
    glBegin(GL_TRIANGLE_STRIP);
    //glVertex3d(0.0,0.0,0.0);
    for (int ii=0; ii<count; ++ii) {
        OGRPoint *point = (OGRPoint *) points->getGeometryRef(ii);
        glVertex3d(-point->getX(), point->getY(), point->getZ() - (height/2));
        glVertex3d(-point->getX(), point->getY(), point->getZ() + (height/2));

    }
    glEnd();


    //botton
    glColor4d(color.red,color.green,color.blue,0.2);
    //glTranslated(0.0,0.0,height);
    glTranslated(0.0,0.0,-height/2);
    glBegin(GL_TRIANGLE_STRIP);
    //glVertex3d(10.0,0.0,0.0);
    for (int ii=0; ii<count; ++ii) {
        OGRPoint *point = (OGRPoint *) points->getGeometryRef(ii);
        glVertex3d(point->getX(), point->getY(), point->getZ());
        glVertex3d(-point->getX(), point->getY(), point->getZ());
    }
    glEnd();
    glEndList();
    ////end of create the list



    //draw arrow according to the points

    /////part of drawing the arrow according to the point destination et point original

    int nbPoints = pointList->getNumGeometries();



    //draw each arrow
    for(int i = 0; i < nbPoints-1; i++) {

        //OGRPoint point_head(-25.0,37.0,0.0);
        //OGRPoint point_tail(50.0,15.0,0.0);

        //define the index necessary to draw the arrow
        /// from point_origin to point_destination
        /// --centre:: the center of the two points


        /// --angle:: calcule arrording to the two points
        /// --index_angle:: index of rotating
        /// //+1 the next point is in the clockwise direction of the line, the arrow turn in the Counterclockwise direction, glRotated(+angle)
        /// //-1 the next point is in the Counterclockwise direction of the line, the arrow turn in the clockwise direction, glRotated(-angle)
        /// --index_length_x
        /// --index_length_y
        /// --index_length_z

        OGRPoint *point_origin = (OGRPoint *) pointList->getGeometryRef(i);
        OGRPoint *point_destination = (OGRPoint *) pointList->getGeometryRef(i+1);

        OGRPoint centre((point_origin->getX()+point_destination->getX())/2.0, (point_origin->getY()+point_destination->getY())/2.0,
                        (point_origin->getZ()+point_destination->getZ())/2.0);


        double yy = point_destination->getY()-point_origin->getY();
        double xx = point_destination->getX()-point_origin->getX();

        //angle of the arrow / angle of the line
        double angle = atan2(yy,xx) * 180 / M_PI;

        //index of angle
        int index_angle = -1;
        double pp = 0;
        if(i < nbPoints-2 ) {
            OGRPoint *point_next = (OGRPoint *) pointList->getGeometryRef(i+2);

            pp = xx*point_next->getY() - point_next->getX() * yy;

            //pp = (point_origin->getX()-point_next->getX())*(point_destination->getY()-point_next->getY())-
                   // (point_origin->getY()-point_next->getY())*(point_destination->getX()-point_next->getX());

        }
        //std::cout << " when ii == " << i << "   " << " pp == " << pp << " "<< std::endl;
        if(pp < 0) {//in the clockwise direction
            index_angle = +1;
        } else if (pp == 0){ //in the Counterclockwise direction
            index_angle = -1;
        } else {
            index_angle = -1;
        }

        //length arrow is according to the radius
        double length_arrow = 2.0*sqrtf(radius*radius*3/4.0);


        //distance enter two points
        double distance = point_origin->Distance(point_destination);



        double index_length_x =distance / length_arrow ;
        //std::cout << "index x" << index_length_x << std::endl;
        //double index_length_x = 2.0;
        double index_length_y = distance / length_arrow ; //length par defalt pour chaque flash 30
        double index_length_z = 1.0;

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LESS);


        glLoadIdentity();

        glPushMatrix();
        glPointSize(2.0);

        //std::cout << "index length y " << index_length_y << std::endl;

        glScaled(index_length_x,index_length_y,0.0);//zoom the arrow

        glTranslated(centre.getX()/index_length_x,(centre.getY())/index_length_y,centre.getZ()/index_length_z);//move the center of arrow to the center of line

        glRotated(angle+90,0.0,0.0,1.0);//rotating the arrow , the length of an arrow is 30

        //glRotated(30,0.0,radius,0.0);//

        if(index_angle == 1 ) {
            glRotated(+30,0.0,radius,0.0);//
        } else {
            glRotated(-30,0.0,radius,0.0);//
        }

       // glRotated(90.0,0.0,radius,0.0);
        glCallList(index);



        glPopMatrix();
        glDisable(GL_DEPTH_TEST);

    }

*/

}

