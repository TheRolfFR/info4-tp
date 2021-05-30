#-------------------------------------------------
#
# Project created by QtCreator 19-01-2018
#
#-------------------------------------------------


### ------------------------------------->
QT += core gui opengl network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
CONFIG += console c++14
TARGET = mobilityVanet
QMAKE_CXXFLAGS += -Wall -Wextra
release: DESTDIR = ./release
release: OBJECTS_DIR = ./obj
### -------------------------------------<


### ------------------------------------->
INCLUDEPATH += "$$PWD/include" $$PWD/../core/include $$PWD/../gui/include $$PWD/../osm
win32: INCLUDEPATH += c:/msys/1.0/local/include
else:unix: INCLUDEPATH += /usr/include/gdal /usr/include/freetype2
### -------------------------------------<


### ------------------------------------->
win32: DEPENDPATH += c:/msys/1.0/local/include $$PWD/../geologic-core/include $$PWD/../libgeologic-gui/include $$PWD/../geologic-osm
### -------------------------------------<


### ------------------------------------->
win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgdal
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgdal
else:unix: LIBS += -lgdal

win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -llibGeographic.dll
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -llibGeographic.dll
else:unix: LIBS += -lGeographic

win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgeos
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgeos

win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lproj
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lproj

win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lshp
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lshp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../geologic-core/release/ -lgeologic-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../geologic-core/debug/ -lgeologic-core
else:unix: LIBS += -L$$PWD/../geologic-core/release/ -lgeologic-core

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libgeologic-gui/release/ -lgeologic-gui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libgeologic-gui/release/ -lgeologic-gui
else:unix: LIBS += -L$$PWD/../libgeologic-gui/release/ -lgeologic-gui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../geologic-osm/release/ -lgeologic-osm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../geologic-osm/release/ -lgeologic-osm
else:unix: LIBS += -L$$PWD/../geologic-osm/release/ -lgeologic-osm


win32:LIBS += -lopengl32 -lglu32 -lglut -lmingw32 -lm
else:unix: LIBS += -lGL -lglut -lGLU -lGeographic -lshp # -lreadosm

### -------------------------------------<


### ------------------------------------->
#HEADERS += \

SOURCES += \
    boundariesdata.cpp \
    boundariesmaterial.cpp \
    boundariesobject.cpp \
    mygeologicbaseclass.cpp \
    src/launcher.cpp

### -------------------------------------<

HEADERS += \
    boundariesdata.h \
    boundariesmaterial.h \
    boundariesobject.h \
    mygeologicbaseclass.h

