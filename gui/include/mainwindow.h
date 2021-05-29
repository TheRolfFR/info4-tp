#pragma once

#include <QString>
#include <QToolBar>
#include <QDockWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QSlider>
#include <QTimeEdit>
#include <QMainWindow>
#include <QMenu>
#include <QStatusBar>
#include <memory>
#include <QLabel>
#include <OpenGL/gldisplay.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    GLDisplay *getGlPanel() const {return gl_panel;}
    QTabWidget *getTabs() {return tabs;}
    QMenu *getMainMenu() {return mainMenu;}
    void setMessage(const char *msg);
    QSlider *getCurrentTimeSlider() {return _advance_slider;}

private:
    QToolBar *tools;
    QDockWidget *dock;
    QTabWidget *tabs;
    QMenu *mainMenu;
    GLDisplay *gl_panel;
    QStatusBar *status_bar;
    QLabel *status_text;
    QLabel *fps_text;
    QLabel *time_text;

    // Toolbar simulation widgets
    QPushButton *_play_pause_btn;
    QPushButton *_stop_btn;
    QTimeEdit *_start_time_selector;
    QTimeEdit *_end_time_selector;
    QSlider *_time_scale_slider;
    QSlider *_advance_slider;

signals:

public slots:
    void playPauseSwap();
    void stopClicked();
    void setStartTime(const QTime &time);
    void setStopTime(const QTime &time);
    void setCurrentTime(int value);
    void setTimeScale(int value);
};
