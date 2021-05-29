#ifndef GEOLOGICAPPLICATION_H
#define GEOLOGICAPPLICATION_H

#include <QApplication>
#include <geologic-core/core/GeologicModule.h>
#include <geologic-core/core/geologic-launcher/CoordinateSystemManager.h>
#include <mainwindow.h>
#include <OpenGL/gldisplay.h>
#include <Scene/movableview.h>
#include <memory>
#include <Common/config.h>
#include <preferenceswindow.h>
#include <QFileDialog>

class MyGPXChooser: public QFileDialog {
    Q_OBJECT

public:
    MyGPXChooser(QWidget *parent, const char *title);

public slots:
    void getSelectedFile(const QString &filename);
};

class GeologicApplication : public QApplication
{
    Q_OBJECT

private:
    std::unique_ptr<MainWindow> main_window;
    std::unique_ptr<MyGPXChooser> _gpx_selection;
    //MainWindow* main_window;
    MovableView *main_view;
    Config cfg;
    QMenu *_tools_menu;
    std::unique_ptr<PreferencesWindow> _preferences_window;

public:
    GeologicApplication(int &argc, char **argv);
    ~GeologicApplication();
    MainWindow *getMainWindow() const;
    void setMainWindow(MainWindow *value);
    Config &getConfig() {return cfg;}
};

#endif // GEOLOGICAPPLICATION_H
