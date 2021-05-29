#pragma once

#include <OpenGL/shader.h>
#include <OpenGL/texture.h>
#include <QVector2D>
#include <Common/color.h>
#include <memory>

class Material {
private:
    const std::string m_name;

    std::map<std::string, std::shared_ptr<Texture>> m_textures;
    std::map<std::string, QVector4D> m_colors;
    
    std::map<std::string, bool&> m_uniforms_bool_ref;
    std::map<std::string, int> m_uniforms_int;
    std::map<std::string, QVector2D> m_uniforms_vec2;
    
    std::map<GLenum, bool> m_options;

    GLuint m_displayMode;

    float m_pointSize;
    float m_lineWidth;

public:
    Material(std::string name);
    virtual ~Material();

    virtual void bind(Shader* shader);

    void setTexture(std::string name, std::shared_ptr<Texture> t) { m_textures[name] = t; };
    void setColor(std::string name, QVector4D c) { m_colors[name] = c; };
    void setColor(std::string name, Color c) { m_colors[name] = QVector4D(c.red, c.green, c.blue, c.alpha); };

    void addUniform(std::string name, bool &b) { m_uniforms_bool_ref.insert(std::pair<std::string, bool&>(name, b)); };
    void addUniform(std::string name, int i) { m_uniforms_int[name] = i; };
    void addUniform(std::string name, QVector2D v) { m_uniforms_vec2[name] = v; };
    
    std::string getName() { return m_name; };

    bool getOption(GLenum option) { return m_options[option]; };

    GLuint getDisplayMode() { return m_displayMode; };
    float getPointSize() { return m_pointSize; };
    float getLineWidth() { return m_lineWidth; };

    void setOption(GLuint name, bool value) { m_options[name] = value; };

    void setDisplayMode(GLuint m) { m_displayMode = m; };
    void setPointSize(float s) { m_pointSize = s; };
    void setLineWidth(float w) { m_lineWidth = w; };
};
