#pragma once

#define GL_GLEXT_PROTOTYPES
#include <QGLFunctions>
#include <QtOpenGL/QtOpenGL>

#include <string>
#include <vector>

#include <OpenGL/shader.h>
#include <OpenGL/texture.h>

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) (static_cast<char*>(0) + (offset))
#endif

class Data: public QThread {
protected:
    std::string m_name;

    GLuint m_eboIndices;
    GLuint m_vboVertices;
    GLuint m_vboUVs;
    GLuint m_vao;
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<float> m_uvs;

    GLuint m_structureType;
	
    bool m_preloaded;
    bool m_loaded;

    bool m_generic;

public:
    Data(std::string &n);
    Data(const char *n);
    virtual ~Data();
    virtual void draw() = 0;

    void bind();

    std::string getName() { return m_name; };
    void setName(std::string n) { m_name = n; };
    
    void setVertices(std::vector<float> v) { m_vertices = v; };
    void setIndices(std::vector<unsigned int> i) { m_indices = i; };
    void setUVs(std::vector<float> u) { m_uvs = u; };
    void setStructureType(GLuint t) { m_structureType = t; };

    void setPreloaded(bool pre) { m_preloaded = pre; };

    bool& getLoadedRef() { return m_loaded; };
    bool getLoaded() { return m_loaded; };
    bool getPreloaded() { return m_preloaded; };
    
    virtual void load();

    void preload() { m_preloaded = true; /*start();*/ };
    void run() { preloadThread(); };
    virtual void preloadThread() { m_preloaded = true; };
};
