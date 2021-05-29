#ifndef SHADER_H
#define SHADER_H

#include <string>

#define GL_GLEXT_PROTOTYPES
#include <QGLFunctions>
#include <QtOpenGL/QtOpenGL>

class Shader
{
private:
    GLuint m_programID;

    GLuint m_vertexID;
    GLuint m_geometryID;
    GLuint m_fragmentID;

    std::string m_vertexShaderFile;
    std::string m_geometryShaderFile;
    std::string m_fragmentShaderFile;

    bool m_usingGeometryShader;

    bool compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource);

public:

    Shader(std::string shaderName = "default");
    virtual ~Shader();

    bool load();
    void bind();
    void unbind();

    GLuint getSubroutineIndex(GLenum shader_type, std::string name);

    void bindSubroutine(GLenum shader_type, GLuint index);

    void setUniformValue(std::string name, int &i);
    void setUniformValue(std::string name, long unsigned int &i);
    void setUniformValue(std::string name, float &f);
    void setUniformValue(std::string name, QVector2D &v);
    void setUniformValue(std::string name, QVector3D &v);
    void setUniformValue(std::string name, QVector4D &v);
    void setUniformValue(std::string name, QMatrix4x4 &m);
    
    void setUniformValues(std::string name, GLuint size, float* f);
};

#endif
