#include "zones.h"
#include <string>
#include <iostream>
#include <ogr_geometry.h>
#include <algorithm>
#include <array>
#include <utility>
#include <random>
#include <memory>
#include <Common/utils.hpp>

using namespace std;

OGRSpatialReference *Zones::getViewref() const {
    return _viewref;
}

void Zones::setViewref(OGRSpatialReference *viewref) {
    _viewref = viewref;
}

Zones::Zones() {
    geo_ref.importFromEPSG(4326);
    zones_boundaries.assignSpatialReference(&geo_ref);
}

void Zones::load(const char *filename) {
    string filename_std = filename;
    OSMLoader loader;
    if (loader.loadOSMfile(filename_std) == -1)
        return;

    OGRLayer *polygons_layer = loader.get_dataset()->GetLayer(3);
    if (!polygons_layer)
        return;

    OGRFeature *feature = polygons_layer->GetNextFeature();
    while (feature) {
        for (auto polygon: feature->GetGeometryRef()->toMultiPolygon()) {
            _zones_polygons.addGeometryDirectly(polygon->clone());
            OGRLinearRing *poly_boundary = polygon->getExteriorRing();
            if (wkbFlatten(poly_boundary->getGeometryType()) == wkbLineString)
                zones_boundaries.addGeometry(poly_boundary->toLineString());
        }
        feature = polygons_layer->GetNextFeature();
    }
}
