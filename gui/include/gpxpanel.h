#ifndef GPXPANEL_H
#define GPXPANEL_H

#include <QWidget>
#include <QPushButton>
#include <OpenGL/gldisplay.h>
#include <QGridLayout>
#include <Data/simplegpxparser.h>
#include <vector>
#include <QMainWindow>
#include <geologic-core/core/geologic-launcher/GPXReader.h>
#include <Object/trajectoryobject.h>
#include <layercheckbox.h>

class GPXPanel: public QWidget {
    Q_OBJECT

    QPushButton *_open_file_btn;
    QPushButton *_delete_btn;
    GLDisplay *_gl_display;
    QGridLayout *_tab_layout;
    QMainWindow *_app_window;

    QVBoxLayout *_vbox_layout;
    QWidget* _ctrl_panel;

    //std::vector<GPXData> _tracks;

    std::vector<std::pair<std::string, std::string>> _tracks;
    QWidget* _cp_layer = nullptr;

public:
    GPXPanel(QWidget *parent, GLDisplay *gld, QMainWindow *main_window, QVBoxLayout* vbox_layout);
    virtual ~GPXPanel() {}
    QGridLayout *getLayout() {return _tab_layout;}

public slots:
    void onOpenFileClicked();
    void onDeleteTrackClicked();
    void onFileSelected(const QString &);
};

#endif // GPXPANEL_H
