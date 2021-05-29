#include "Material/material.h"
#include <iostream>

using namespace std;

Material::Material(std::string name):
    m_name(name),
    m_displayMode(GL_FILL),
    m_pointSize(2.0f),
    m_lineWidth(2.0f)
{}


Material::~Material() {
}


void Material::bind(Shader* shader) {
    int i = 0;
    for(auto t: m_textures)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, t.second->getTexture());

        int ready = t.second->isReady();
        shader->setUniformValue(t.first + "_ready", ready);
        shader->setUniformValue(t.first, i); 
        i++;
    }

    for(auto c: m_colors)
    {
        shader->setUniformValue(c.first, c.second);
    }

    for(auto b: m_uniforms_bool_ref)
    {
        int val = b.second;
        shader->setUniformValue(b.first, val);
    }

    for(auto i: m_uniforms_int)
    {
        shader->setUniformValue(i.first, i.second);
    }

    for(auto i: m_uniforms_vec2)
    {
        shader->setUniformValue(i.first, i.second);
    }

    for(auto i: m_options) {
        if(i.second)
            glEnable(i.first);
        else
            glDisable(i.first);
    }

    glPointSize(m_pointSize);
    glLineWidth(m_lineWidth);
    glPolygonMode(GL_FRONT_AND_BACK, m_displayMode);
}
