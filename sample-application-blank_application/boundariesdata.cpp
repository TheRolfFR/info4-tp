#include <gdal.h>
#include <gdal/gdal_priv.h>
#include <gdal/ogr_geometry.h>
#include <gdal/ogrsf_frmts.h>
#include "boundariesdata.h"
#include <iostream>

#include "osmloader.h"
#include "geologic-core/core/geologic-launcher/CoordinateSystemManager.h"

BoundariesData::BoundariesData() : UniqueData("MyData"), loader() {
     std::vector<float> tmp_vertices;
     GDALAllRegister();

     //data
     GDALDataset *ds = nullptr;

     // laod file
     int res = loader.loadOSMfile("france-boundaries.osm");

     if(res != 0) {
         std::cout << "Empty osm file provided: " << std::endl;
         throw "Empty osm file";
         exit(-1);
     }

     ds = loader.get_dataset();

     OGRLayer *layer = ds->GetLayer(3);
     OGRFeature *feature = layer->GetNextFeature();
     OGRGeometry *geometry = feature->GetGeometryRef();
     OGRMultiPolygon *boundaries = reinterpret_cast<OGRMultiPolygon *>(geometry);
     OGRPolygon *france_mainland = reinterpret_cast<OGRPolygon *>(boundaries->getGeometryRef(64)); // We tried before, so we know it is 64
     OGRLinearRing *france_outer = france_mainland->getExteriorRing();
     france_outer->assignSpatialReference(CoordinateSystemManager::getInstance()->getDataRef());
     OGRCoordinateTransformation *t = OGRCreateCoordinateTransformation(
                                            CoordinateSystemManager::getInstance()->getDataRef(),
                                            CoordinateSystemManager::getInstance()->getViewRef());
     if (t) france_outer->transform(t);
     OCTDestroyCoordinateTransformation(t);
     for (int i=0; i<france_outer->getNumPoints(); ++i) {
         OGRPoint p;
         france_outer->getPoint(i, &p);
         tmp_vertices.push_back(p.getX());
         tmp_vertices.push_back(p.getY());
         tmp_vertices.push_back(0.0);
     }
     setVertices(tmp_vertices);
     setStructureType(GL_LINE_STRIP);
     GDALClose(ds);
}
