#include <Scene/view.h>
#include <geologic-core/utils/customToolbox.h>
#include <iostream>

#include <Scene/uniquelayer.h>

#include <Object/backgroundobject.h>

using namespace std;

View::View():
    m_visible(true),
    m_screen_width(1),
    m_screen_height(1),
    m_screen_left(0),
    m_screen_top(0),
    m_resized(true),
    m_projection(),
    m_view() {
    m_update_tree = std::make_unique<RootObject>(this);
    m_background = new BackgroundObject(0, 0, 0, 0.3);
//    m_background = new BackgroundObject(1, 1, 1, 0.3);
}

View::~View() {
}


void View::setPosition(int left, int top) {
    m_screen_left = left;
    m_screen_top = top;
}


void View::setSize(int width, int height) {
    m_screen_width = width;
    m_screen_height = height;
    m_resized = true;
    updateView();
}


void View::update(double t) {
    m_update_tree->update(t);
}


void View::initViewport() {
    glViewport(m_screen_left, m_screen_top, m_screen_width, m_screen_height);
}


void View::draw() {
    initViewport();
    if(m_visible) {
        m_background->draw();
        for(auto& layer: m_render_tree) {
            layer->draw(m_projection, m_view);
        }
    }
}


void View::drawCheckboxes(QWidget* tab, QLayout* layout) {
    for(auto& layer: m_render_tree) {
        layer->drawCheckbox(tab, layout);
    }
}


void View::addObject(Object* obj) {
    m_update_tree->addChild(obj);
}


Layer* View::addRenderObject(std::string layer, ChildObject* obj) {
    Layer* l;
    try {
        l = m_layers.at(layer);
        l->addChild(obj);
    } catch (std::out_of_range &e) {
        //std::cout << "No layer named " << layer << std::endl;
        l = nullptr;
    }
    return l;
}


void View::addLayer(std::string layer) {
    Layer* l = new UniqueLayer(layer);
    m_layers.insert(std::pair<std::string, Layer*>(layer, l));
    m_render_tree.push_back(l);
}


void View::addLayer(std::string layer, Layer* l) {
    m_layers.insert(std::pair<std::string, Layer*>(layer, l));
    m_render_tree.push_back(l);
}
