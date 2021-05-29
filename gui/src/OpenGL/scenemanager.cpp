#include <OpenGL/scenemanager.h>
#include <geologic-core/utils/customToolbox.h>

using std::cout;
using std::endl;

SceneManager::SceneManager():
    m_main_view(),
    m_simu_clock(),
    m_screen_width(1),
    m_screen_height(1),
    m_is_running(false),
    m_is_paused(false),
    m_simu_start(0),
    m_simu_end(0),
    m_controller(),
    m_label(),
    m_needs_view_update(true) {}


SceneManager::~SceneManager() {}


void SceneManager::init() {
    m_main_view = std::make_unique<MovableView>();
    m_controller = std::make_unique<Controller>();
}


double SceneManager::update() {
    double time = m_simu_clock.getCurrentTime(); 
    if (m_is_running && !m_is_paused) {
        m_simu_clock.update();
        if (time > m_simu_end) {
            m_is_running = false;
            m_simu_clock.stop();
            time = m_simu_end;
        }
        m_needs_view_update = true;
    }

    if(m_needs_view_update) {
        realUpdate(time);
    }

    m_controller->check();

    return time;
}


void SceneManager::realUpdate(double t) {
    m_main_view->update(t);
    m_needs_view_update = false;
}


void SceneManager::needsViewUpdate() {
    m_needs_view_update = true;
} 


void SceneManager::resize(QVector2D& size) {
    m_screen_width = size.x();
    m_screen_height = size.y();
    setWindowSize(size);
    glViewport (0, 0, (GLsizei) m_screen_width, (GLsizei) m_screen_height);
    needsViewUpdate();
};


void SceneManager::draw() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glClearColor(0.25, 0.45, 0.65, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_main_view->draw();
}


void SceneManager::start() {
    if (m_simu_start < m_simu_end) {
        if(!m_is_paused)
            m_simu_clock.setInitialTime(m_simu_start);
        m_is_running = true;
        m_is_paused = false;
        m_simu_clock.start();
    }
}


void SceneManager::pause() {
    m_is_paused = true;
    m_simu_clock.pause();
}


void SceneManager::stop() {
    m_is_running = false;
    m_simu_clock.stop();
}


void SceneManager::updateLabel(QVector2D pos) {
    CoordinateSystemManager* geoRefs = CoordinateSystemManager::getInstance();
    m_label = geoRefs->getCSName(geoRefs->getDisplayRef()) + " " + std::to_string(pos.x()) + ", " + std::to_string(pos.y()) + " (EPSG:" + customToolbox::str(geoRefs->getDisplayRef()->GetEPSGGeogCS()) + ")";
}


void SceneManager::wheelEvent(QWheelEvent * event) {
    if (event) {
        if (event->delta() > 0)
            m_controller->wheelEvent(1);
        else
            m_controller->wheelEvent(-1);
        event->accept();
    }
}


void SceneManager::setWindowSize(QVector2D& s) {
    m_main_view->setSize(s.x(), s.y());
}


void SceneManager::mouseMoveEvent(QMouseEvent * event) {
    m_controller->mouseEvent(event->pos().x(), event->pos().y());
    event->accept();
}


void SceneManager::mousePressEvent(QMouseEvent * event) {
    m_controller->clickEvent(event->button(), 1);
    event->accept();
}


void SceneManager::mouseReleaseEvent(QMouseEvent * event) {
    m_controller->clickEvent(event->button(), 0);
    event->accept();
}


void SceneManager::keyPressEvent(QKeyEvent *event) {
    m_controller->keyEvent(event->key(), 1);
    event->accept();
}


void SceneManager::keyReleaseEvent(QKeyEvent *event) {
    m_controller->keyEvent(event->key(), 0);
    event->accept();
}
