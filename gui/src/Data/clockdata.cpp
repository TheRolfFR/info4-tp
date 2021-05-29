#include <Data/clockdata.h>
#include <OpenGL/quaddisplayer.h>


/**
 * \brief 	Default constructor of class ClockData
 *
 * \param 	None
 * \return 	None
 */
ClockData::ClockData(): Data("ClockData") {

    std::vector<float> vertices = {0,0,0};

    setVertices(vertices);
    setStructureType(GL_POINTS);

}

/**
 * \brief 	Default destructor of class ClockData
 *
 * \param 	None
 * \return 	None
 */
ClockData::~ClockData(){}

/**
 * \brief 	Inherited method from class Data
 *
 * \param 	None
 * \return 	None
 */
/*void ClockData::draw() {

    this->drawBackGround();
    unsigned long long currentTime = this->s_clock->getCurrentTime();

    int hours = (currentTime / 3600) % 24; //à chercher dans SimulationClock
    int minutes = (currentTime % 3600) / 60;//à chercher dans SimulationClock
    int seconds =  (currentTime % 3600) % 60;
    char string_time[9];
    sprintf(string_time, "%02d:%02d:%02d", hours, minutes, seconds); // Clock dans un buffer text

    // dessin police / valeur compteur
    glColor4f(0.0, 0.0, 0.0, 1.0); // Couleur caractères
    glLineWidth(3);// Épaisseur des caractères
    glPointSize(3);

    char *p;
    glPushMatrix();
    glTranslatef(-125, -40.0, 0.0);
    glScaled(0.6, 1.4, 1.0);

    for (p = &string_time[0]; *p; p++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); // Vectoriser et afficher chaque caractère.
    }

    glPopMatrix();
}*/


/**
 * \brief 	Inherited method from class Data
 *
 * \param 	t   a time_t
 * \return 	None
 *
 */
//void ClockData::draw(unsigned long long t) {
//    this->draw();
//}

/**
 * \brief 	Display the background of the view
 *
 * \param 	None
 * \return 	None
 *
 *
 */
void ClockData::drawBackGround() {

    OGRPoint* corner[4];
    OGRPoint BL = OGRPoint(-150.0, -150.0);
    corner[0] = &BL;

    OGRPoint BR = OGRPoint(200.0, -150.0);
    corner[1] = &BR;

    OGRPoint TR = OGRPoint(200.0, 200.0);
    corner[2] = &TR;

    OGRPoint TL = OGRPoint(-150.0, 200.0);
    corner[3] = &TL;

    QuadDisplayer::drawQuad(corner, Color(1, 1, 1, 0.7));
}
