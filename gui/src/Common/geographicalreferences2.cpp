#include "geographicalreferences.h"
#include <geologic-core/utils/customToolbox.h>
#include <cstring>
#include <iostream>

using namespace std;

GeographicalReferences::GeographicalReferences() {
    customToolbox::start("GeographicalReferences::GeographicalReferences");
    viewRef = make_unique<OGRSpatialReference>();
    displayRef = make_unique<OGRSpatialReference>();
    dataRef = make_unique<OGRSpatialReference>();
    //dataRef->importFromEPSG(4326);
    customToolbox::end("GeographicalReferences::GeographicalReferences");
}

GeographicalReferences::~GeographicalReferences() {}
