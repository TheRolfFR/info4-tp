#include <OpenGL/framebuffer.h>

#include <iostream>
#include <fstream>

#include <ResourceManagement/datamanager.h>
#include <Material/framebuffermaterial.h>

#include <layercheckbox.h>

#include <QOpenGLFunctions>

using namespace std;

Framebuffer::Framebuffer(std::shared_ptr<Shader> shader, std::string framebufferName):
    ChildObject(shader, framebufferName),
    m_fbo(),
    m_rbo(),
    m_sub_layers()
{
    m_material = std::make_shared<FramebufferMaterial>(shader);
    setData(DataManager::getInstance()->get("quad"));
}


Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_fbo);
}


void Framebuffer::draw(QMatrix4x4 &projection, QMatrix4x4 &view) {
    QMatrix4x4 model;
    draw(projection, view, model);
}

/*!
 * \brief Draws the object itself if it has data and a material, then calls a draw for the children
 */
void Framebuffer::draw(QMatrix4x4 &projection, QMatrix4x4 &view, QMatrix4x4 &model) {
    for(auto& f: m_sub_layers) {
        f->draw(projection, view, model);
    }
    ChildObject::draw(projection, view, model);
}


void Framebuffer::clear() {
    bind();
    glClearColor(0.0, 0, 0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    unbind();
    for(auto& f: m_sub_layers) {
        f->clear();
    }
}


bool Framebuffer::load(int width, int height) {
    // ===== Frame buffer =====
    m_screen_width = width;
    m_screen_height = height;

    // Destruction d'un éventuel ancien Framebuffer
	if (glIsFramebuffer(m_fbo) == GL_TRUE)
        glDeleteFramebuffers(1, &m_fbo);

    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // ===== Target texture =====
    m_texture = std::make_shared<Texture>();
    m_texture->loadEmpty(width, height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getTexture(), 0);  
    getMaterial()->setTexture("tex", m_texture);

    // ===== Render buffer =====
    // Destruction d'un éventuel ancien Framebuffer
	if (glIsRenderbuffer(m_rbo) == GL_TRUE)
        glDeleteRenderbuffers(1, &m_rbo);

    glGenRenderbuffers(1, &m_rbo);

    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);  
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);  
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);  

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    for(auto& f: m_sub_layers) {
        f->load(width, height);
    }

    return 0;
}


void Framebuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glGetIntegerv(GL_VIEWPORT, &m_last_viewport[0]);
    glViewport(0, 0, (GLsizei) m_screen_width, (GLsizei) m_screen_height);
}


void Framebuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(m_last_viewport[0], m_last_viewport[1], m_last_viewport[2], m_last_viewport[3]);
}


void Framebuffer::drawCheckboxes(QWidget *tab, QVBoxLayout *layout) {
    if (tab != nullptr && layout != nullptr) {
        auto my_checkbox = new LayerCheckBox(this, QObject::tr(getName().c_str()), tab);
        layout->addWidget(my_checkbox);

        if(m_sub_layers.size()) {
            auto myLayout = new QVBoxLayout();
            myLayout->setContentsMargins(10, 0, 0, 0);
            layout->addLayout(myLayout);
            for(auto& f: m_sub_layers) {
                f->drawCheckboxes(tab, myLayout);
            }
        }
    }
}


void Framebuffer::setHidden() {
    ChildObject::setHidden();
    for(auto& o: m_attached) {
        o->setHidden();
    }
}


void Framebuffer::setVisible() {
    ChildObject::setVisible();
    for(auto& o: m_attached)
        o->setVisible();
}


void Framebuffer::toggleVisibility() {
    ChildObject::toggleVisibility();
    for(auto& o: m_attached)
        o->toggleVisibility();
}
