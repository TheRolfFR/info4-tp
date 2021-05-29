#pragma once

#include <string>

#define GL_GLEXT_PROTOTYPES
#include <QGLFunctions>
#include <QtOpenGL/QtOpenGL>
#include <Object/childobject.h>
#include <OpenGL/texture.h>

class Framebuffer: public ChildObject {
private:
    GLuint m_fbo;
    GLuint m_rbo;
    std::shared_ptr<Texture> m_texture;
    int m_screen_width;	///< Screen/frame width, pixels
    int m_screen_height;	///< Screen/frame height, pixels
    GLint m_last_viewport[4];

    std::vector<Object*> m_attached;

    std::vector<std::shared_ptr<Framebuffer>> m_sub_layers;

public:
    Framebuffer(std::shared_ptr<Shader> shader, std::string shaderName = "default");
    virtual ~Framebuffer();
    
    virtual void draw(QMatrix4x4 &projection, QMatrix4x4 &view);
    virtual void draw(QMatrix4x4 &projection, QMatrix4x4 &view, QMatrix4x4 &model);

    void clear();

    bool load(int width, int height);
    void bind();
    void unbind();
    
    void drawCheckboxes(QWidget *tab, QVBoxLayout *layout);

    void attach(Object* o) { m_attached.push_back(o); o->setHidden(m_hidden); };
    void detach(Object* o) { m_attached.erase(std::find(m_attached.begin(), m_attached.end(), o)); };

    void addLayer(std::shared_ptr<Framebuffer> l) { m_sub_layers.push_back(l); };

    virtual void setHidden();
    virtual void setVisible();
    virtual void toggleVisibility();
};
