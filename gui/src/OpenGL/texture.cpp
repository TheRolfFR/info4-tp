#include <OpenGL/texture.h>
#include <QString>
#include <QFile>
#include <QImage>

#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <QGLFunctions>
#include <QtOpenGL/QtOpenGL>

using namespace std;

Texture::Texture(): tex(0), loaded(false) {}

void Texture::loadFromFile(const string &filename)
{
    loadFromFile(filename.c_str());
}

void Texture::loadFromFile(const char *filename)
{
    QString file_as_qstring = QFile::decodeName(filename);

    if(QFile::exists(file_as_qstring)) {
        glEnable(GL_TEXTURE_2D); // Enable texturing

        glGenTextures(1, &tex); // Obtain an id for the texture
        if (tex != 0) {
            glBindTexture(GL_TEXTURE_2D, tex); // Set as the current texture

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

            QImage im(file_as_qstring);
            QImage texture = QGLWidget::convertToGLFormat(im);

            if (!texture.isNull()) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());
                loaded = true;
            } else {
                glDeleteTextures(1, &tex);
            }

        }
        glDisable(GL_TEXTURE_2D);
    }
}


void Texture::loadFromData(GLsizei width, GLsizei height, const GLvoid* data) {
    glEnable(GL_TEXTURE_2D); // Enable texturing

    glGenTextures(1, &tex); // Obtain an id for the texture
    if (tex != 0) {
        glBindTexture(GL_TEXTURE_2D, tex); // Set as the current texture

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            width,
            height,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            data
        );
        loaded = true;
    }
    glDisable(GL_TEXTURE_2D);
}

void Texture::loadEmpty(unsigned int width, unsigned int height) {
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::clearTexture() {
    if (tex != 0)
        glDeleteTextures(1, &tex);
}
