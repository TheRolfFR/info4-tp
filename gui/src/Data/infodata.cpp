#include <Data/infodata.h>
#include <memory>
#include "geologic-core/utils/customToolbox.h"

using namespace customToolbox;

/**
 * \brief 	Default constructor of class infoData
 *
 * \param 	None
 * \return 	None
 */
infoData::infoData(): Data("infoData") {
    this->initInfo();
    std::vector<float> vertices = {0,0,0};

    setVertices(vertices);
    setStructureType(GL_POINTS);
}

/**
 * \brief 	Default destructor of class infoData
 *
 * \param 	None
 * \return 	None
 */
infoData::~infoData() {}


/**
 * \brief 	Initialize the information
 *
 * \param 	None
 * \return 	None
 */
void infoData::initInfo() {
    this->id = "ID null";
    time_t currentTime = 0;
    string_time_begin = "Begin " + str(currentTime, true); // Time begin in string
    string_time_end = "End " + str(currentTime, true); // Time end in string
    string_time_durant = "Duration " + str(currentTime, true); // Duration in string

    char char_distance[20];
    std::sprintf(char_distance, "Distance %.2lfKm", 0.0);// Distance dans un buffer text
    string_distance = char_distance; // Distance in string
}



/**
 * \brief 	Set the information
 *
 * \param 	id       Id of the object
 * \param   t_begin  Time_t of the beginning
 * \param   t_end    Time_t of the end
 * \param   distance double in distance
 *
 * \return 	None
 */
void infoData::setInfo(int id, time_t t_begin, time_t t_end, double distance) {
    this->id = "ID " + std::to_string(id); // Id in string
    string_time_begin = "Begin " + str(t_begin, true); // Time begin in string
    string_time_end = "End " + str(t_end, true);// Time end in string
    string_time_durant = "Duration " + str(t_end - t_begin, true); // Time duration in string

    char char_distance[20];
    std::sprintf(char_distance, "Distance %.2lfm", distance); // Distance dans un buffer text
    string_distance = char_distance; // Distance in string
}


/**
 * \brief 	Inherited method from class Data
 *
 * \param 	None
 * \return 	None
 *
 *
 */
/*void infoData::draw() {

    if (id != "ID null") {
        //Display the background
        drawBackGround();

        // Dessin police / valeur compteur
        glColor4f(0.0, 0.0, 0.0, 1.0);
        glLineWidth(1.75);
        glPointSize(1.75);
        char *p;

        //Display id
        glPushMatrix();
        glTranslatef(-135, 160,0.0);
        glScaled(0.25, 0.15, 1.0);
        for (p = &id[0]; *p; p++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); // Display every character in string id
        }
        glPopMatrix();

        // display the time begin
        //glColor4d(0, 1, 0, 1.0);
        glPushMatrix();
        glTranslatef(-135, 120,0.0);
        glScaled(0.25, 0.15, 1.0);
        for (p = &string_time_begin[0]; *p; p++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); // Display every character in string time begin

        }
        glPopMatrix();

        // display the time end
        //glColor4d(1, 0, 0, 1.0);
        glPushMatrix();
        glTranslatef(-135, 70,0.0);
        glScaled(0.25, 0.15, 1.0);
        for (p = &string_time_end[0]; *p; p++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); // Display every character in string time end
        }
        glPopMatrix();

        // diaplay the duration
        //glColor4f(0.0, 0.0, 0.0, 1.0);
        glPushMatrix();
        glTranslatef(-135, 20,0.0);
        glScaled(0.25, 0.15, 1.0);
        for (p = &string_time_durant[0]; *p; p++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); // Display every character in string time duration
        }
        glPopMatrix();

        // display the distance
        glPushMatrix();
        glTranslatef(-135, -30,0.0);
        glScaled(0.25, 0.15, 1.0);
        for (p = &string_distance[0]; *p; p++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); // Display every character in string distance
        }
        glPopMatrix();
    }
}*/


/**
 * \brief 	Inherited method from class Data
 *
 * \param 	t   a time_t
 * \return 	None
 *
 *
 */
/*void infoData::draw(unsigned long long t) {
    this->draw();
}*/


/**
 * \brief 	Display the background of the view
 *
 * \param 	None
 * \return 	None
 *
 *
 */
void infoData::drawBackGround() {

    OGRPoint* corner[4];
    OGRPoint BL = OGRPoint(-150.0, -250.0);
    corner[0] = &BL;

    OGRPoint BR = OGRPoint(200.0, -250.0);
    corner[1] = &BR;

    OGRPoint TR = OGRPoint(200.0, 200.0);
    corner[2] = &TR;

    OGRPoint TL = OGRPoint(-150.0, 200.0);
    corner[3] = &TL;

    QuadDisplayer::drawQuad(corner, Color(1, 1, 1, 0.8));



    glColor4d(0, 1, 0, 0.4); //green
    glPointSize(20.0);
    glBegin(GL_POINTS);
    glVertex3d(-110, -70.0, 0.0);
    glEnd();


    glColor4d(1, 0, 0, 0.4); //red
    glPointSize(20.0);
    glBegin(GL_POINTS);
    glVertex3d(-110, -120.0, 0.0);
    glEnd();


    glColor4d(1, 1, 0, 0.4); //gold
    glPointSize(20.0);
    glBegin(GL_POINTS);
    glVertex3d(-110, -170.0, 0.0);
    glEnd();

    glColor4f(0.0, 0.0, 0.0, 1.0);
    glLineWidth(1);
    glPointSize(1);
    char *p;

    // point origin
    std::string st_begin = "Origin";
    glPushMatrix();
    glTranslatef(-50, -80,0.0);
    glScaled(0.25, 0.15, 1.0);
    for (p = &st_begin[0]; *p; p++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); // Display every character in string distance
    }
    glPopMatrix();

    // point destination
    std::string st_end = "Destination";
    glPushMatrix();
    glTranslatef(-50, -130,0.0);
    glScaled(0.25, 0.15, 1.0);
    for (p = &st_end[0]; *p; p++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); // Display every character in string distance
    }
    glPopMatrix();


    // point courant
    std::string st_cour = "Current";
    glPushMatrix();
    glTranslatef(-50, -180,0.0);
    glScaled(0.25, 0.15, 1.0);
    for (p = &st_cour[0]; *p; p++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); // Display every character in string distance
    }
    glPopMatrix();

}
