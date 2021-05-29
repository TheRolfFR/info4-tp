#include "gpxpanel.h"
#include <QString>
#include <QFileDialog>
#include <iostream>
#include <geologic-core/utils/customToolbox.h>

using namespace std;

GPXPanel::GPXPanel(QWidget *parent, GLDisplay *gld, QMainWindow *main_window, QVBoxLayout* vbox_layout): QWidget(parent), _gl_display(gld), _app_window(main_window), _vbox_layout(vbox_layout), _ctrl_panel(parent) {
    _tab_layout = new QGridLayout;
    setLayout(_tab_layout);
    _open_file_btn = new QPushButton(tr("Add GPX"), this);
    _delete_btn = new QPushButton(tr("Delete"), this);
    _tab_layout->addWidget(_open_file_btn, 0, 0);
    _tab_layout->addWidget(_delete_btn, 0, 1);
    connect(_open_file_btn, SIGNAL(clicked()), this, SLOT(onOpenFileClicked()));
}

void GPXPanel::onOpenFileClicked() {
    QFileDialog *file_dialog = new QFileDialog(_app_window, tr("Open File"), tr("."));
    connect(file_dialog, SIGNAL(fileSelected(const QString &)), this, SLOT(onFileSelected(const QString &)));
    file_dialog->show();
}

void GPXPanel::onDeleteTrackClicked() {

}

void GPXPanel::onFileSelected(const QString &filename) {
    if (!filename.isNull()) {
        // Read, import and convert
        GPXReader* gpxr = GPXReader::getInstance();
        gpxr->load(filename.toStdString(), CoordinateSystemManager::getInstance()->getDataRef(), CoordinateSystemManager::getInstance()->getDisplayRef());

        MobileObject* mobile = gpxr->getMobile();
        Trajectory* tt = mobile->listTrajectories["0"];
        tt->dummyFill(10);

        //We add a composite layer, and add all trakcs as single layer inside it
        if (_tracks.size() <= 0) {
            QWidget* tmp = _vbox_layout->itemAt(_vbox_layout->count()-1)->widget();
            if (tmp == nullptr) _vbox_layout->takeAt(_vbox_layout->count()-1);

//            auto cp_layer = std::make_unique<CompositeLayer>();
//            cp_layer->setTitle("User added GPX tracks");
//            _cp_layer = cp_layer->drawCheckbox(_ctrl_panel, _vbox_layout); //will add as a widget
            _vbox_layout->addStretch();
            //_gl_display->getMainView()->addLayer(std::move(cp_layer));
        }

//        if (_cp_layer != nullptr) {
//            CompositeLayer* cp_layer = ((CompositeLayer*) ((LayerCheckBox*) _cp_layer)->managed_layer);

       //     TrajectoryObject* traj = new TrajectoryObject(tt);
//            auto pt_layer = std::make_unique<SingleLayer>(new TrajectoryObject(tt));
     //       string track_name = customToolbox::split(customToolbox::split(filename.toStdString(), '/').back(), '.')[0];
      //      string real_track_name = track_name;
     //       unsigned occ = 0;
    //        for (unsigned int i=0; i<_tracks.size(); i++) if (_tracks[i].first == track_name) occ++;
    //        if (occ > 0) real_track_name = track_name + "_" + customToolbox::str(occ);
            //pt_layer->getObject()->setName(real_track_name);
   //         _tracks.push_back(pair<string, string>(track_name, real_track_name));

            //cp_layer->addChild(pt_layer.get());
            //cp_layer->updateCheckbox(_ctrl_panel, pt_layer.get());
            //_gl_display->getMainView()->addLayer(std::move(pt_layer));
  //      }
    }
}
