# Geologic core manual

Geologic core is the root library for geologic projects. It handles data types related to mobility as well as some basic algorithms such as clustering. It is used by all the other geologic libraries.

## Installation

### Required packages
Geologic core requires several packages to be compiled.
#### Ubuntu and derived

Under ubuntu and derived distributions, those packages can be installed with the following command:
`sudo apt install git qtcreator g++ qt5-qmake qt5-default build-essential libgdal-dev libgeographic-dev libshp-dev`

#### Fedora

Under Fedora, those packages can be installed with the following command:
`sudo dnf install qt-creator gcc-c++ qt5-devel gdal-devel GeographicLib-devel shapelib-devel`

#### Windows

TBD

### Compiling

Open the .pro file with Qt Creator. It may ask you which kit to use, use the default Qt5 kit. Then choose which type of compilation you want (debug, profile, or release), then hit the Build button (or press Ctrl-B). Wait for the compilation to be done (it may take a few minutes). You shall see the following result in the compilation output panel:

```
(... omitted ...)
rm -f release/libgeologic-core.so
rm -f release/libgeologic-core.so.1
rm -f release/libgeologic-core.so.1.0
mv -f libgeologic-core.so release/libgeologic-core.so
mv -f libgeologic-core.so.1 release/libgeologic-core.so.1
mv -f libgeologic-core.so.1.0 release/libgeologic-core.so.1.0
```

## Howto

TBD: Étienne
