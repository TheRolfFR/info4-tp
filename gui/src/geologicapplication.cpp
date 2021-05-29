#include "geologicapplication.h"

#include <Simulation/simulationclock.h>
#include <Scene/movableview.h>
#include <geologic-core/utils/customToolbox.h>
#include <ogr_geometry.h>
#include <QMenuBar>
#include <QMenu>

#include <iostream>

using namespace std;

MainWindow *GeologicApplication::getMainWindow() const {
    return main_window.get();
}

void GeologicApplication::setMainWindow(MainWindow *value) {
    main_window.reset(value);
    //delete(main_window);
    //main_window = value;
}

GeologicApplication::GeologicApplication(int &argc, char **argv): QApplication(argc, argv) {
//    GeologicModule* core = GeologicModule::getInstance();
    glutInit(&argc, argv);
    //main_window = make_unique<MainWindow>();
    //main_window = new MainWindow();
    //main_window->setWindowTitle(tr("My GIS interface"));

    main_window = make_unique<MainWindow>();
    main_window->setWindowTitle(tr("My GIS interface"));

    customToolbox::start("GeologicApplication::GeologicApplication");
    if (argc == 2) {
        cfg.load(argv[1]); // Load configuration file, if provided
    }

    CoordinateSystemManager* geoReferences = CoordinateSystemManager::getInstance();
    geoReferences->setReferences(geoReferences->getCSbyRef(cfg.data_epsg_code).get(),
                                 geoReferences->getCSbyRef(cfg.view_epsg_code).get(),
                                 geoReferences->getCSbyRef(cfg.view_epsg_code).get());

    GLDisplay *glpanel = main_window->getGlPanel();
    if (glpanel != nullptr && geoReferences->getDataRef() != nullptr) {
        //glpanel->setGeoRefs();
        OGRPoint view_center{cfg.x, cfg.y};
        view_center.assignSpatialReference(geoReferences->getDataRef());
    } else {
        cout << "HAAAAAA" << endl;
    }
    _tools_menu = main_window->menuBar()->addMenu(QObject::tr("Tools"));
    _preferences_window = make_unique<PreferencesWindow>(&cfg);
    _tools_menu->addAction(QObject::tr("Preferences"), _preferences_window.get(), SLOT(show()));
    _gpx_selection = make_unique<MyGPXChooser>(main_window.get(), "Choose GPX file");
    _tools_menu->addAction(QObject::tr("Add GPX track"), _gpx_selection.get(), SLOT(show()));

    customToolbox::end("GeologicApplication::GeologicApplication");
    //*/
}

GeologicApplication::~GeologicApplication() {
    //cout << "GeologicApplication::~GeologicApplication()" << endl;
}

MyGPXChooser::MyGPXChooser(QWidget *parent, const char *title): QFileDialog(parent, tr(title), tr("."), tr("GPX files (*.gpx)")) {
    connect(this, SIGNAL(fileSelected(const QString &)), this, SLOT(getSelectedFile(const QString &)));
}

void MyGPXChooser::getSelectedFile(const QString &filename) {
    cout << "Selected: " << filename.toStdString() << endl;
}
