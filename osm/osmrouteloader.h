#ifndef OSMROUTELOADER_H
#define OSMROUTELOADER_H

//#include "geologic-osm_global.h"
#include <osmloader.h>
#include <string>
#include <vector>
#include <memory>
#include <ogr_geometry.h>
#include <ogr_spatialref.h>
// #include <Data/data.h>
// #include <Common/color.h>
#include <geologic-core/objects/urban/roadloader.h>

class OSMLoader;
class Node;
class Edge;

class OSMRouteLoader: public RoadLoader {
private:
    std::unique_ptr<OSMLoader> loader;
    bool isFootEdge(const char *type);
    bool isCarEdge(const char *type);
    bool isCycleEdge(const char *type);
//    int isOneWay(const char *type);
//    std::string edgeType(osm_way_t *w);

public:
    OSMRouteLoader(OGRSpatialReference *ref): RoadLoader(ref) {loader = std::make_unique<OSMLoader>();}
    virtual int load(std::string &filename);

    OSMLoader *getLoader() const;
    void setLoader(std::unique_ptr<OSMLoader> &value);

    void convertGeogCS(OGRSpatialReference *ref); // OSM: always WGS84

    virtual void load(const char *filename);
    virtual void load(const std::string &filename);

protected:
};
/**/
#endif // OSMROUTELOADER_H
