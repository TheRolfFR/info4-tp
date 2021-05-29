#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T17:42:11
#
#-------------------------------------------------


### ------------------------------------->
QT += network opengl xml core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = lib
CONFIG += c++11
TARGET = geologic-gui
QMAKE_CXXFLAGS += -Wall -Wextra
release: DESTDIR = ./release
release: OBJECTS_DIR = ./obj
### -------------------------------------<


### ------------------------------------->
INCLUDEPATH += "$$PWD/include" $$PWD/../core-master/include $$PWD/../osm-master/
win32: INCLUDEPATH += c:/msys/1.0/local/include
else:unix: INCLUDEPATH += /usr/include/gdal /usr/include/freetype2
### -------------------------------------<


### ------------------------------------->
win32: DEPENDPATH += c:/msys/1.0/local/include $$PWD/../core/include
### -------------------------------------<


### ------------------------------------->
win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgdal
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgdald
else:unix: LIBS += -lgdal

win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -llibGeographic.dll
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -llibGeographic.dlld

win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgeos
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgeosd

win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lproj
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lprojd

win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lshp
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lshpd

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../geologic-core/release/ -lgeologic-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../geologic-core/debug/ -lgeologic-core
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-geologic-core-Desktop-Debug/release/ -lgeologic-core
else:unix:: LIBS += -L$$PWD/../build-geologic-core-Desktop-Release/release/ -lgeologic-core


win32::LIBS += -lopengl32 -lglu32 -lmingw32 -lfreeglut
else:unix: LIBS += -lglut -lm -lfreetype
### -------------------------------------<


### ------------------------------------->
#geologicgui.cpp \
SOURCES +=    src/mainwindow.cpp \
    src/Data/ogr_point_data.cpp \
    src/Material/ogr_point_material.cpp \
    src/Object/ogr_point_object.cpp \
    src/geologicapplication.cpp \
    src/Simulation/simulationclock.cpp \
    src/layercheckbox.cpp \
    src/preferenceswindow.cpp \
    src/gpxpanel.cpp \
    src/Common/utils2.cpp \
    src/Common/config.cpp \
    src/Common/triangle.cpp \
    src/Common/controller.cpp \
    src/Common/triangulation.cpp \
    src/OpenGL/shader.cpp \
    src/OpenGL/texture.cpp \
    src/OpenGL/gldisplay.cpp \
    src/OpenGL/scenemanager.cpp \
    src/OpenGL/loadingmanager.cpp \
    src/Scene/view.cpp \
    src/Scene/layer.cpp \
    src/Scene/uniquelayer.cpp \
    src/Scene/genericlayer.cpp \
    src/Scene/fixedview.cpp \
    src/Scene/movableview.cpp \
    src/Data/data.cpp \
    src/Data/uniquedata.cpp \
    src/Data/genericdata.cpp \
    src/Data/griddata.cpp \
    src/Data/meshdata.cpp \
    src/Data/linedata.cpp \
    src/Data/quaddata.cpp \
    src/Data/pointdata.cpp \
    src/Data/staticdata.cpp \
    src/Data/signalmanager.cpp \
    src/Data/rastertiledata.cpp \
    src/Data/vectortiledata.cpp \
    src/Data/simplegpxparser.cpp \
    src/Object/object.cpp \
    src/Object/textobject.cpp \
    src/Object/characterobject.cpp \
    src/Object/backgroundobject.cpp \
    src/Object/rootobject.cpp \
    src/Object/parentobject.cpp \
    src/Object/childobject.cpp \
    src/Object/tileobject.cpp \
    src/Object/generatorobject.cpp \
    src/Object/rastertileobject.cpp \
    src/Object/vectortileobject.cpp \
    src/Material/material.cpp \
    src/Material/linematerial.cpp \
    src/Material/circlematerial.cpp \
    src/Material/rastertilematerial.cpp \
    src/Material/vectortilematerial.cpp \
    src/ResourceManagement/datamanager.cpp \
    src/ResourceManagement/shadermanager.cpp \
    src/ResourceManagement/texturemanager.cpp \
    src/ResourceManagement/texturedownloader.cpp \
    src/ResourceManagement/tiletexturemanager.cpp \
    src/ResourceManagement/vectortiledatamanager.cpp \
    src/ResourceManagement/vectortiledatadownloader.cpp

HEADERS +=     include/mainwindow.h \
    include/Data/ogr_point_data.h \
    include/Material/ogr_point_material.h \
    include/Object/ogr_point_object.h \
    include/defines.h \
    include/gpxpanel.h \
    include/layercheckbox.h \
    include/preferenceswindow.h \
    include/geologicapplication.h \
    include/Common/color.h \
    include/Common/config.h \
    include/Common/utils2.h \
    include/Common/utils.hpp \
    include/Common/triangle.h \
    include/Common/controller.h \
    include/Common/triangulation.h \
    include/Simulation/simulationclock.h \
    include/OpenGL/shader.h \
    include/OpenGL/texture.h \
    include/OpenGL/gldisplay.h \
    include/OpenGL/scenemanager.h \
    include/OpenGL/loadingmanager.h \
    include/Scene/view.h \
    include/Scene/layer.h \
    include/Scene/uniquelayer.h \
    include/Scene/genericlayer.h \
    include/Scene/fixedview.h \
    include/Scene/movableview.h \
    include/Data/data.h \
    include/Data/uniquedata.h \
    include/Data/genericdata.h \
    include/Data/mesh.hpp \
    include/Data/quaddata.h \
    include/Data/griddata.h \
    include/Data/meshdata.h \
    include/Data/linedata.h \
    include/Data/pointdata.h \
    include/Data/staticdata.h \
    include/Data/signalmanager.h \
    include/Data/rastertiledata.h \
    include/Data/vectortiledata.h \
    include/Data/simplegpxparser.h \
    include/Object/object.h \
    include/Object/textobject.h \
    include/Object/characterobject.h \
    include/Object/backgroundobject.h \
    include/Object/rootobject.h \
    include/Object/tilegrid.hpp \
    include/Object/tileobject.h \
    include/Object/generatorobject.h \
    include/Object/rastertileobject.h \
    include/Object/vectortileobject.h \
    include/Material/material.h \
    include/Material/linematerial.h \
    include/Material/circlematerial.h \
    include/Material/rastertilematerial.h \
    include/Material/vectortilematerial.h \
    include/ResourceManagement/datamanager.h \
    include/ResourceManagement/shadermanager.h \
    include/ResourceManagement/texturemanager.h \
    include/ResourceManagement/resourcemanager.hpp \
    include/ResourceManagement/texturedownloader.h \
    include/ResourceManagement/tiletexturemanager.h \
    include/ResourceManagement/vectortiledatamanager.h \
    include/ResourceManagement/vectortiledatadownloader.h
#geologicgui.h\
#geologic-gui_global.h
### -------------------------------------<


### ------------------------------------->
unix {
    target.path = /usr/lib
    INSTALLS += target
}
### -------------------------------------<
