#include "OpenGL/gldisplay.h"
#include <QColor>
#include <QWheelEvent>
#include <iostream>
#include <QtOpenGL/QtOpenGL>
#include <QSurfaceFormat>
#include <geologic-core/utils/customToolbox.h>
#include <exception>
#include <mainwindow.h>
#include <memory.h>
#include <cmath>
#include <Data/testdata.h>
#include <OpenGL/arrow3ddisplayer.h>

#include <ResourceManagement/shadermanager.h>
#include <ResourceManagement/texturemanager.h>
#include <ResourceManagement/texturedownloader.h>
#include <OpenGL/loadingmanager.h>
#include <ResourceManagement/vectortiledatadownloader.h>
#include <ResourceManagement/datamanager.h>

using namespace std;

/*!
 * \brief GLDisplay::GLDisplay constructor inherited from QOpenGLWidget
 * Sets the parent widget, and sets various settings required to interact properly with GLDisplay
 * \param parent pointer to a parent widget
 */
GLDisplay::GLDisplay(/*const QGLFormat& format,*/ QWidget *parent): QOpenGLWidget(/*format,*/ parent) {
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
}

/*!
 * \brief GLDisplay::~GLDisplay destructor
 * If scene manager is allocated, deletes it.
 */
GLDisplay::~GLDisplay() {
    if (m_scene_manager)
        delete m_scene_manager;
}

/*!
 * \brief GLDisplay::initializeGL initializes the GL panel
 * Loads shaders, textures, and data managers
 */
void GLDisplay::initializeGL() {
    initializeOpenGLFunctions();
    ShaderManager::getInstance()->load();
    TextureManager::getInstance()->load();
    DataManager::getInstance()->load();

    gettimeofday(&_last_sec, nullptr);
}

/*!
 * \brief GLDisplay::paintGL draws everything on screen
 * First: updates data sources and statuses
 * Second: updates graphics status
 * Third: updates FPS counter
 */
void GLDisplay::paintGL() {
//    cout << "paintGL" << endl;
    TextureDownloader::getInstance()->update(); //Try to download a new texture if there is a pending demand
    VectorTileDataDownloader::getInstance()->update(); //Try to download a new vector tile if there is a pending demand
    LoadingManager::getInstance()->update(); //Try to load a Data object into GPU if there is a pending demand
    
    //Update
    if(m_scene_manager) {
        if(m_resized) {
            m_scene_manager->resize(m_window_size);
            m_resized = false;
        }

        double newTime = m_scene_manager->update(); //Next time tick and layers update
        if (this->parent() && reinterpret_cast<MainWindow *>(this->parent())->getCurrentTimeSlider())
            reinterpret_cast<MainWindow *>(this->parent())->getCurrentTimeSlider()->setValue(newTime);

        if (_time_label) {
            _time_label->setText(QString::fromStdString(customToolbox::str((int)newTime, true))); //display time as HH:MM:SS
            _time_label->update();
        }
       
        MainWindow *p = (MainWindow *) parent();
        if (p)
            p->setMessage(m_scene_manager->getLabel().c_str());

        m_scene_manager->draw();
    }/* else {
      cout << "Scene manager is null" << endl;
    }*/
    update(); // Shall detect if new data requires screen refresh

    // FPS calculation
    ++_images;
    struct timeval current_time;
    gettimeofday(&current_time, nullptr);
    if (current_time.tv_sec > _last_sec.tv_sec) {
        double fps = static_cast<double>(_images) / (current_time.tv_sec - _last_sec.tv_sec);
        if (_fps_label) {
            _fps_label->setNum(fps);
            _fps_label->update();
        }
        _images = 0;
        _last_sec.tv_sec = current_time.tv_sec;
    }
//    cout << "Exiting GLDisplay::PaintGL" << endl;
}


void GLDisplay::resizeGL(int w, int h) {
    m_window_size = QVector2D(w, h);
    m_resized = true;
}


void GLDisplay::wheelEvent(QWheelEvent * event) {
    if (m_scene_manager) {
        m_scene_manager->wheelEvent(event);
    }
}


void GLDisplay::mouseMoveEvent(QMouseEvent * event) {
    if (m_scene_manager) {
        m_scene_manager->mouseMoveEvent(event);
    }
}


void GLDisplay::mousePressEvent(QMouseEvent * event) {
    if (m_scene_manager) {
        m_scene_manager->mousePressEvent(event);
    }
}


void GLDisplay::mouseReleaseEvent(QMouseEvent * event) {
    if (m_scene_manager) {
        m_scene_manager->mouseReleaseEvent(event);
    }
}


void GLDisplay::keyPressEvent(QKeyEvent *event) {
    if (m_scene_manager) {
        m_scene_manager->keyPressEvent(event);
        update();
    }
}


void GLDisplay::keyReleaseEvent(QKeyEvent *event) {
    if (m_scene_manager) {
        m_scene_manager->keyReleaseEvent(event);
        update();
    }
}


void GLDisplay::setGeoRefs() {
}
