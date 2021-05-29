#ifndef GEOGRAPHICALREFERENCES_H
#define GEOGRAPHICALREFERENCES_H

#include <ogr_spatialref.h>
#include <ogr_geometry.h>
#include <memory>

/*!
 * \brief The GeographicalReferences class manages
 * the geographical coordinates and projections systems used throughout the library.
 */
class GeographicalReferences
{
private:
    std::unique_ptr<OGRSpatialReference> dataRef;       ///< Reference used in data
    std::unique_ptr<OGRSpatialReference> viewRef;       ///< Reference used in OpenGL View
    std::unique_ptr<OGRSpatialReference> displayRef;    ///< Reference used for displaying in status bar

public:
    GeographicalReferences();
    ~GeographicalReferences();

    OGRSpatialReference *getDataRef() { return dataRef.get(); }
    OGRSpatialReference *getViewRef() { return viewRef.get(); }
    OGRSpatialReference *getDisplayRef() { return displayRef.get(); }
};

#endif // GEOGRAPHICALREFERENCES_H
