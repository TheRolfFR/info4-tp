
### ------------------------------------->
QT += core
TEMPLATE = lib
CONFIG += console c++14
TARGET = geologic-core
QMAKE_CXXFLAGS += -Wno-missing-field-initializers -Wno-implicit-fallthrough
release: DESTDIR = ./release
release: OBJECTS_DIR = ./obj
### -------------------------------------<



### ------------------------------------->
INCLUDEPATH += "$$PWD/include"
win32: INCLUDEPATH += c:/msys/1.0/local/include
else:unix: INCLUDEPATH += /usr/include/gdal
### -------------------------------------<



### ------------------------------------->
win32: DEPENDPATH += c:/msys/1.0/local/include
### -------------------------------------<



### ------------------------------------->
win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgdal
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgdal
else:unix: LIBS += -lgdal


win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -llibGeographic.dll
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -llibGeographic.dll


win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgeos
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lgeos


win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lproj
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lproj


win32:CONFIG(release, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lshp
else:win32:CONFIG(debug, debug|release): LIBS += -Lc:/msys/1.0/local/lib/ -lshp
### -------------------------------------<



### ------------------------------------->
# include/geologic-core/core/geologic-core_global.h \
# include/geologic-core/core/geologiccore.h \

HEADERS += \
    include/geologic-core/algorithms/geoMetrics/geoMetrics.h \
    include/geologic-core/algorithms/json/json-forwards.h \
    include/geologic-core/algorithms/json/json.h \
    include/geologic-core/algorithms/shapefile/GeoZoneShapefile.h \
    include/geologic-core/algorithms/trajectories/Bspline.h \
    include/geologic-core/algorithms/trajectories/TrajectoryManager.h \
    include/geologic-core/core/geologic-launcher/CoordinateSystemManager.h \
    include/geologic-core/core/geologic-launcher/GeologicLauncher.h \
    include/geologic-core/core/geologic-launcher/ShapefileReader.h \
    include/geologic-core/core/geologic-launcher/GPXReader.h \
    include/geologic-core/core/geologic-launcher/GeoJsonReader.h \
    include/geologic-core/core/geologic-mapper/geo/CoordinateSystemMap.h \
    include/geologic-core/core/geologic-mapper/geo/CoordinateTransformationMap.h \
    include/geologic-core/core/geologic-mapper/geo/GeoZoneHierarchyMap.h \
    include/geologic-core/core/geologic-mapper/geo/GeoZoneMap.h \
    include/geologic-core/core/geologic-mapper/social/IndividualMap.h \
    include/geologic-core/core/geologic-mapper/transportation/TransportationTypeMap.h \
    include/geologic-core/core/geologic-mapper/GeologicMapper.h \
    include/geologic-core/core/GeologicModule.h \
    include/geologic-core/graphe/Edge.h \
    include/geologic-core/graphe/Node.h \
    include/geologic-core/graphicTemplates/GeologicCustomizeObject.h \
    include/geologic-core/graphicTemplates/GeologicGeometricalObject.h \
    include/geologic-core/graphicTemplates/GeologicGraphicalObject.h \
    include/geologic-core/graphicTemplates/GeologicGraphicalObjectFlow.h \
    include/geologic-core/graphicTemplates/GeologicGraphicalObjectMobile.h \
    include/geologic-core/graphicTemplates/GeologicGraphicalObjectShape.h \
    include/geologic-core/objects/dynamic/Displacement.h \
    include/geologic-core/objects/dynamic/GraphMobileObject.h \
    include/geologic-core/objects/dynamic/MobileObject.h \
    include/geologic-core/objects/dynamic/Trajectory.h \
    include/geologic-core/objects/dynamic/Trip.h \
    include/geologic-core/objects/geo/temporal/TemporalGeoData.h \
    include/geologic-core/objects/geo/temporal/TemporalGeoPoint.h \
    include/geologic-core/objects/geo/temporal/TemporalGeoZone.h \
    include/geologic-core/objects/geo/untemporal/MeshGrid.h \
    include/geologic-core/objects/geo/untemporal/Bbox.h \
    include/geologic-core/objects/geo/untemporal/GeoZone.h \
    include/geologic-core/objects/geo/untemporal/GeographicalObject.h \
    include/geologic-core/objects/geo/untemporal/Grid.h \
    include/geologic-core/objects/geo/untemporal/GridMesh.h \
    include/geologic-core/objects/social/Individual.h \
    include/geologic-core/objects/transportation/Car.h \
    include/geologic-core/objects/transportation/Cycle.h \
    include/geologic-core/objects/transportation/Footman.h \
    include/geologic-core/objects/transportation/TransportationType.h \
    include/geologic-core/objects/urban/roadloader.h \
    include/geologic-core/objects/urban/roads.h \
    include/geologic-core/roles/permissions/CarPermission.h \
    include/geologic-core/roles/permissions/CyclePermission.h \
    include/geologic-core/roles/permissions/EmptyPermission.h \
    include/geologic-core/roles/permissions/FootPermission.h \
    include/geologic-core/roles/permissions/Permission.h \
    include/geologic-core/roles/restrictions/EmptyRestriction.h \
    include/geologic-core/roles/restrictions/NoturnRestriction.h \
    include/geologic-core/roles/restrictions/OnewayRestriction.h \
    include/geologic-core/roles/restrictions/Restriction.h \
    include/geologic-core/roles/Role.h \
    include/geologic-core/roles/RoleDynamics.h \
    include/geologic-core/roles/RoleGeo.h \
    include/geologic-core/roles/RoleIndividualManager.h \
    include/geologic-core/roles/RoleManager.h \
    include/geologic-core/roles/RoleModule.h \
    include/geologic-core/roles/RoleRoadNetworkManager.h \
    include/geologic-core/roles/RoleTransportationPlannerAuthority.h \
    include/geologic-core/superClasses/Mapper.h \
    include/geologic-core/superClasses/Metadata.h \
    include/geologic-core/superClasses/Module.h \
    include/geologic-core/superClasses/Parser.h \
    include/geologic-core/utils/customToolbox.h \
    include/geologic-core/utils/customToolbox_impl.h \
    include/geologic-core/algorithms/clustering/ClusteringEnvironment.h \
    include/geologic-core/algorithms/clustering/GeologicCluster.h \
    include/geologic-core/algorithms/clustering/kmeans/Kmeans.h \
    include/geologic-core/algorithms/clustering/kmeans/ClusterKmeans.h \
    include/geologic-core/algorithms/clustering/dbscan/DBscan.h \
    include/geologic-core/algorithms/clustering/hierarchical/Hierarchical.h \
    include/geologic-core/algorithms/clustering/hierarchical/ClusterHCA.h

SOURCES += \
    src/geologic-core/algorithms/geoMetrics/geoMetrics.cpp \
    src/geologic-core/algorithms/json/jsoncpp.cpp \
    src/geologic-core/algorithms/shapefile/GeoZoneShapefile.cpp \
    src/geologic-core/algorithms/trajectories/Bspline.cpp \
    src/geologic-core/algorithms/trajectories/TrajectoryManager.cpp \
    src/geologic-core/core/geologic-launcher/CoordinateSystemManager.cpp \
    src/geologic-core/core/geologic-launcher/GeologicLauncher.cpp \
    src/geologic-core/core/geologic-launcher/ShapefileReader.cpp \
    src/geologic-core/core/geologic-launcher/GPXReader.cpp \
    src/geologic-core/core/geologic-launcher/GeoJsonReader.cpp \
    src/geologic-core/core/geologic-mapper/geo/CoordinateSystemMap.cpp \
    src/geologic-core/core/geologic-mapper/geo/CoordinateTransformationMap.cpp \
    src/geologic-core/core/geologic-mapper/geo/GeoZoneHierarchyMap.cpp \
    src/geologic-core/core/geologic-mapper/geo/GeoZoneMap.cpp \
    src/geologic-core/core/geologic-mapper/social/IndividualMap.cpp \
    src/geologic-core/core/geologic-mapper/transportation/TransportationTypeMap.cpp \
    src/geologic-core/core/geologic-mapper/GeologicMapper.cpp \
    src/geologic-core/core/GeologicModule.cpp \
    src/geologic-core/graphe/Edge.cpp \
    src/geologic-core/graphe/Node.cpp \
    src/geologic-core/graphicTemplates/GeologicCustomizeObject.cpp \
    src/geologic-core/graphicTemplates/GeologicGeometricalObject.cpp \
    src/geologic-core/graphicTemplates/GeologicGraphicalObject.cpp \
    src/geologic-core/graphicTemplates/GeologicGraphicalObjectFlow.cpp \
    src/geologic-core/graphicTemplates/GeologicGraphicalObjectMobile.cpp \
    src/geologic-core/graphicTemplates/GeologicGraphicalObjectShape.cpp \
    src/geologic-core/objects/dynamic/Displacement.cpp \
    src/geologic-core/objects/dynamic/GraphMobileObject.cpp \
    src/geologic-core/objects/dynamic/MobileObject.cpp \
    src/geologic-core/objects/dynamic/Trajectory.cpp \
    src/geologic-core/objects/dynamic/Trip.cpp \
    src/geologic-core/objects/geo/temporal/TemporalGeoData.cpp \
    src/geologic-core/objects/geo/temporal/TemporalGeoPoint.cpp \
    src/geologic-core/objects/geo/temporal/TemporalGeoZone.cpp \
    src/geologic-core/objects/geo/untemporal/Bbox.cpp \
    src/geologic-core/objects/geo/untemporal/GeoZone.cpp \
    src/geologic-core/objects/geo/untemporal/GeographicalObject.cpp \
    src/geologic-core/objects/geo/untemporal/Grid.cpp \
    src/geologic-core/objects/geo/untemporal/GridMesh.cpp \
    src/geologic-core/objects/social/Individual.cpp \
    src/geologic-core/objects/transportation/Car.cpp \
    src/geologic-core/objects/transportation/Cycle.cpp \
    src/geologic-core/objects/transportation/Footman.cpp \
    src/geologic-core/objects/transportation/TransportationType.cpp \
    src/geologic-core/objects/urban/roadloader.cpp \
    src/geologic-core/objects/urban/roads.cpp \
    src/geologic-core/roles/permissions/CarPermission.cpp \
    src/geologic-core/roles/permissions/CyclePermission.cpp \
    src/geologic-core/roles/permissions/EmptyPermission.cpp \
    src/geologic-core/roles/permissions/FootPermission.cpp \
    src/geologic-core/roles/restrictions/EmptyRestriction.cpp \
    src/geologic-core/roles/restrictions/NoturnRestriction.cpp \
    src/geologic-core/roles/restrictions/OnewayRestriction.cpp \
    src/geologic-core/roles/Role.cpp \
    src/geologic-core/roles/RoleDynamics.cpp \
    src/geologic-core/roles/RoleGeo.cpp \
    src/geologic-core/roles/RoleIndividualManager.cpp \
    src/geologic-core/roles/RoleManager.cpp \
    src/geologic-core/roles/RoleModule.cpp \
    src/geologic-core/roles/RoleRoadNetworkManager.cpp \
    src/geologic-core/roles/RoleTransportationPlannerAuthority.cpp \
    src/geologic-core/superClasses/Mapper.cpp \
    src/geologic-core/superClasses/Metadata.cpp \
    src/geologic-core/superClasses/Module.cpp \
    src/geologic-core/superClasses/Parser.cpp \
    src/geologic-core/utils/customToolbox.cpp \
    src/geologic-core/algorithms/clustering/ClusteringEnvironment.cpp \
    src/geologic-core/algorithms/clustering/GeologicCluster.cpp \
    src/geologic-core/algorithms/clustering/kmeans/Kmeans.cpp \
    src/geologic-core/algorithms/clustering/kmeans/ClusterKmeans.cpp \
    src/geologic-core/algorithms/clustering/dbscan/DBscan.cpp \
    src/geologic-core/algorithms/clustering/hierarchical/Hierarchical.cpp \
    src/geologic-core/algorithms/clustering/hierarchical/ClusterHCA.cpp
### -------------------------------------<
