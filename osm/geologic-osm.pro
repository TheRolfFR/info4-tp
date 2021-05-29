#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T17:42:11
#
#-------------------------------------------------


### ------------------------------------->
QT += core network opengl gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = lib
CONFIG += c++14
TARGET = geologic-osm
QMAKE_CXXFLAGS += -Wno-comment -pg -std=c++14 -Wno-unused-parameter -Wno-unused-variable
win32::QMAKE_CXXFLAGS -= -pg
release: DESTDIR = ./release
release: OBJECTS_DIR = ./obj
### -------------------------------------<


### ------------------------------------->
INCLUDEPATH += "$$PWD/include" $$PWD/../geologic-core/include
win32: INCLUDEPATH += c:/msys/1.0/local/include $$PWD/../libgeologic-gui
else:unix: INCLUDEPATH += /usr/include/gdal $$PWD/../gui/include $$PWD/../core/include
### -------------------------------------<


### ------------------------------------->
win32: DEPENDPATH += c:/msys/1.0/local/include $$PWD/../geologic-core/include  $$PWD/../libgeologic-gui/include
else:unix: DEPENDPATH += $$PWD/../core/include  $$PWD/../gui/include
### -------------------------------------<


### ------------------------------------->
win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgdal
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgdald
else:unix: LIBS += -lgdal

#win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lreadosm
#else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lreadosmd

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../geologic-core/release/ -lgeologic-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../geologic-core/debug/ -lgeologic-cored

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libgeologic-gui/release/ -lgeologic-gui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libgeologic-gui/debug/ -lgeologic-guid

win32::LIBS += -lopengl32 -lglu32 -lglut -lmingw32 -lgeologic-gui
### -------------------------------------<


### ------------------------------------->
SOURCES += osmrouteloader.cpp \
    osmloader.cpp \
    zones.cpp \
    tagsbuilder.cpp \
    nominatim.cpp \
    buildings.cpp

#geologic-osm_global.h \
HEADERS += osmrouteloader.h\
    osmloader.h \
    zones.h \
    tagsbuilder.h \
    nominatim.h \
    buildings.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
### -------------------------------------<



