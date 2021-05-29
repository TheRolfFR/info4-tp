#include "mainwindow.h"
#include <QMenuBar>
#include <QLabel>
#include <iostream>
#include <geologic-core/utils/customToolbox.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    customToolbox::start("MainWindow::MainWindow");
    this->setGeometry(200, 100, 800, 600);

    mainMenu = menuBar()->addMenu(tr("&File"));
    if (mainMenu != nullptr)
    {
        mainMenu->addAction(tr("&Quit"), this, SLOT(close()));
    }
    /*QGLFormat glFormat;
 	glFormat.setVersion(4, 5);
  	glFormat.setProfile(QGLFormat::CoreProfile); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers(true);*/
    
    gl_panel = new GLDisplay(this);
    setCentralWidget(gl_panel);
    tools = new QToolBar(this);
    _play_pause_btn = new QPushButton(QIcon("resources/play.xpm"), "Play");
    tools->addWidget(_play_pause_btn);
    connect(_play_pause_btn, SIGNAL(clicked()), this, SLOT(playPauseSwap()));
    _stop_btn = new QPushButton(QIcon("resources/stop.xpm"), "Stop");
    tools->addWidget(_stop_btn);
    connect(_stop_btn, SIGNAL(clicked()), this, SLOT(stopClicked()));
    _start_time_selector = new QTimeEdit;
    tools->addWidget(_start_time_selector);
    _start_time_selector->setTime(QTime(0, 0, 0, 0));
    connect(_start_time_selector, SIGNAL(timeChanged(const QTime &)), this, SLOT(setStartTime(const QTime &)));
    _end_time_selector = new QTimeEdit;
    tools->addWidget(_end_time_selector);
    _end_time_selector->setTime(QTime(24, 0, 0, 0));
    connect(_end_time_selector, SIGNAL(timeChanged(const QTime &)), this, SLOT(setStopTime(const QTime &)));
    _time_scale_slider = new QSlider(Qt::Orientation::Horizontal);
    tools->addWidget(_time_scale_slider);
    _time_scale_slider->setMinimum(1);
    _time_scale_slider->setMaximum(600);
    _time_scale_slider->setValue(60);
    connect(_time_scale_slider, SIGNAL(valueChanged(int)), this, SLOT(setTimeScale(int)));
    _advance_slider = new QSlider(Qt::Orientation::Horizontal);
    tools->addWidget(_advance_slider);
    _advance_slider->setMinimum(0);
    _advance_slider->setMaximum(3600*24);
    _advance_slider->setValue(0);
    connect(_advance_slider, SIGNAL(valueChanged(int)), this, SLOT(setCurrentTime(int)));
    addToolBar(tools);

    status_bar = statusBar();
    status_text = new QLabel(tr(""));
    status_text->setMinimumWidth(450);
    fps_text = new QLabel(tr(""));
    gl_panel->setFpsLabel(fps_text);
    time_text = new QLabel(tr(""));
    gl_panel->setTimeLabel(time_text);
    status_bar->addWidget(status_text);
    status_bar->addWidget(fps_text, 1);
    status_bar->addWidget(time_text, 1);
    status_bar->show();

    tabs = new QTabWidget(this);
    dock = new QDockWidget(this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dock->setWidget(tabs);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    customToolbox::end("MainWindow::MainWindow");
}

MainWindow::~MainWindow() {
    //cout << "MainWindow::~MainWindow()" << endl;
}

void MainWindow::setMessage(const char *msg) {
    status_text->setText(tr(msg));
    status_text->update();
}

void MainWindow::playPauseSwap() {
    SceneManager* scene_manager = gl_panel->getSceneManager();
    if (scene_manager->isRunning() && !scene_manager->isPaused()) {
        scene_manager->pause();
        _play_pause_btn->setIcon(QIcon("resources/play.xpm"));
        _play_pause_btn->setText("Play");
    } else {
        scene_manager->start();
        _play_pause_btn->setIcon(QIcon("resources/pause.xpm"));
        _play_pause_btn->setText("Pause");
    }
}

void MainWindow::stopClicked() {
    SceneManager* scene_manager = gl_panel->getSceneManager();
    scene_manager->stop();
    _play_pause_btn->setIcon(QIcon("resources/play.xpm"));
    _play_pause_btn->setText("Play");
}

void MainWindow::setStartTime(const QTime &time) {
    SceneManager* scene_manager = gl_panel->getSceneManager();
    scene_manager->setSimulationStartTime(time.msecsSinceStartOfDay() / 1000);
    _advance_slider->setMinimum(time.msecsSinceStartOfDay() / 1000);
}

void MainWindow::setStopTime(const QTime &time) {
    SceneManager* scene_manager = gl_panel->getSceneManager();
    scene_manager->setSimulationEndTime(time.msecsSinceStartOfDay() / 1000);
    _advance_slider->setMaximum(time.msecsSinceStartOfDay() / 1000);
}

void MainWindow::setCurrentTime(int value) {
    SceneManager* scene_manager = gl_panel->getSceneManager();
    scene_manager->setSimulationCurrentTime(value);
}

void MainWindow::setTimeScale(int value) {
    SceneManager* scene_manager = gl_panel->getSceneManager();
    scene_manager->setSimulationTimeScale(value);
}
