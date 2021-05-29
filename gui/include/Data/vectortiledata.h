#pragma once

#include <Data/uniquedata.h>
#include <Common/color.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>

#include <geologic-core/graphe/Edge.h>

class VectorTileData : public UniqueData {
private:
    std::string m_filename;
    std::vector<int> m_types;
    GLuint m_vboTypes;

    void setTypes(std::vector<int> types) { m_types = types; };

public:
    VectorTileData();
    ~VectorTileData();

    void load();

    void setFilename(std::string filename) { m_filename = filename; };
    void preloadThread();
};
