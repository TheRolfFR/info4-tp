#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
#include <QTimer>
#include <QLabel>
#include <vector>
#include <memory>
#include <OpenGL/scenemanager.h>
#include <sys/time.h>

class GLDisplay : public QOpenGLWidget, protected QOpenGLFunctions {
//class GLDisplay : public QGLWidget {
    Q_OBJECT

public:
    GLDisplay(/*const QGLFormat& format,*/ QWidget *parent);
    ~GLDisplay();

    void setSceneManager(SceneManager* sm) { m_scene_manager = sm; };
    SceneManager* getSceneManager() { return m_scene_manager; };

    void setFpsLabel(QLabel *lbl) {_fps_label = lbl;}
    void setTimeLabel(QLabel *lbl) {_time_label = lbl;}
    virtual void setGeoRefs();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:

    virtual void wheelEvent(QWheelEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    SceneManager* m_scene_manager;
    QVector2D m_window_size;
    bool m_resized;

    unsigned int _images;                           ///< Image count for FPS calculation
    struct timeval _last_sec;                       ///< FPS calculation: last second update
    QLabel *_fps_label;                             ///< Used to display FPS in status bar
    QLabel *_time_label;                             ///< Used to display time in status bar
};

#endif // GLDISPLAY_H
