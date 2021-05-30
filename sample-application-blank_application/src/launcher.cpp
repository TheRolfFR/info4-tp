/**
 * \file	Launcher.cpp
 * \class	Launcher
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \author  Nicolas Ballet (nicolas.ballet@utbm.fr)
 * \date	01/01/2018
 * \brief	Launcher is the entry point of this project
 */

#include <exception>
#include <iostream>
#include <cmath>

#include "geologicapplication.h"
#include "mainwindow.h"

#include <Common/config.h>
#include <QVBoxLayout>
#include <QTime>
#include <QWidget>
#include <QApplication>
#include <QTabWidget>
#include <zones.h>
#include <nominatim.h>
#include <buildings.h>

#include <memory>
#include <QNetworkProxy>

#include <unordered_map>

#include "geologic-core/algorithms/geoMetrics/geoMetrics.h"
#include "geologic-core/core/geologic-launcher/GPXReader.h"
#include "geologic-core/core/geologic-launcher/GeoJsonReader.h"
#include "geologic-core/algorithms/trajectories/TrajectoryManager.h"
#include <geologic-core/algorithms/clustering/kmeans/Kmeans.h>
#include <geologic-core/algorithms/clustering/dbscan/DBscan.h>
#include <geologic-core/algorithms/clustering/hierarchical/Hierarchical.h>
#include <Data/infodata.h>

#include <ResourceManagement/shadermanager.h>
#include <ResourceManagement/texturemanager.h>
#include <ResourceManagement/tiletexturemanager.h>
#include <ResourceManagement/vectortiledatamanager.h>
#include <ResourceManagement/datamanager.h>
#include <ResourceManagement/texturedownloader.h>

#include <geologic-core/core/geologic-launcher/CoordinateSystemManager.h>

#include "mygeologicbaseclass.h"

int main(int argc, char *argv[]) {

    qsrand(QTime::currentTime().msec());
    CPLSetConfigOption("OGR_CT_FORCE_TRADITIONAL_GIS_ORDER", "YES");
    setlocale(LC_ALL, "C");

    GeologicModule* module = GeologicModule::getInstance();
    module->getRoleName();

    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling); // Fixes wrong viewport on HiDPI systems
    GeologicApplication a(argc, argv);
    MainWindow* t = a.getMainWindow();

    ShaderManager::getInstance()->init();
    TextureManager::getInstance()->init();
    TileTextureManager::getInstance()->init(a.getConfig().tile_url_base);
    VectorTileDataManager::getInstance()->init(a.getConfig().overpass_url_base);
    DataManager::getInstance()->init();
    
    if (a.getConfig().proxy_enabled) { // If configured, set an application wide network proxy
        QNetworkProxy proxy(QNetworkProxy::HttpProxy, a.getConfig().proxy_address, a.getConfig().proxy_port);
        QNetworkProxy::setApplicationProxy(proxy);
    }

    if (t)
        t->show();
    else
        return -1;

    CoordinateSystemManager* geoRefs = CoordinateSystemManager::getInstance();
    OGRPoint view_center{a.getConfig().x, a.getConfig().y};
    view_center.assignSpatialReference(geoRefs->getDataRef());

    // TODO: instantiate a SceneManager child class as my_scene:
    MyGeologicBaseClass *my_scene = new MyGeologicBaseClass(); // Use a relevant name
    my_scene->init();
    my_scene->getMainView()->setZoom(a.getConfig().zoom);
    my_scene->getMainView()->setGeoRefs();
    my_scene->getMainView()->setCenter(view_center);

    a.getMainWindow()->getGlPanel()->setSceneManager(my_scene);

    //FixedView* info = a.getMainWindow()->getGlPanel()->getInfoView();
    QTabWidget* tabs = a.getMainWindow()->getTabs();

    // Build the layers checkbox toggle panel and its layout
    QWidget* ctrl_panel = new QWidget(a.getMainWindow());
    QVBoxLayout* tab_layout = new QVBoxLayout();
    ctrl_panel->setLayout(tab_layout);
    
    QWidget* info_panel = new QWidget(a.getMainWindow());
    QVBoxLayout* info_layout = new QVBoxLayout();
    info_panel->setLayout(info_layout);

    // Finalize the checkboxes panel: add a stretch, and add it to the window.
    tabs->addTab(ctrl_panel, QObject::tr("Couches"));
    tabs->addTab(info_panel, QObject::tr("Infos"));

    // Add an OSM nominatim panel for geocoded search
    NominatimPanel *nom_panel = new NominatimPanel(ctrl_panel, a.getMainWindow()->getGlPanel());
    tabs->addTab(nom_panel, QObject::tr("Search"));

    my_scene->drawCheckboxes(tabs, tab_layout);
    tab_layout->addStretch();

    t->setStopTime(QTime(1, 0, 0, 0));
    t->setTimeScale(1);
    int exit_code = a.exec();

    DataManager::getInstance()->flush();
    ShaderManager::getInstance()->flush();
    TileTextureManager::getInstance()->flush();
    TextureManager::getInstance()->flush();
    TextureDownloader::getInstance()->flushPending();

    delete my_scene;
    return exit_code;
}
