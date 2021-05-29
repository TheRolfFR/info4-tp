#include "osmrouteloader.h"
#include <ogr_spatialref.h>
#include <geologic-core/core/geologic-launcher/CoordinateSystemManager.h>
#include <geologic-core/utils/customToolbox.h>
#include <geologic-core/graphe/Node.h>
#include <geologic-core/graphe/Edge.h>
#include <iostream>
#include <cstdio>

using namespace std;

int OSMRouteLoader::load(std::string &filename) {
    if (loader != nullptr) {
        unsigned long long node_id = 0;
        int ret =  loader->loadOSMfile(filename);
        if (loader->get_dataset() == nullptr)
            return -1;
        OGRLayer *roads_layer = loader->get_dataset()->GetLayer(1);

        OGRFeature *feature = roads_layer->GetNextFeature();
        while (feature) {
            int osm_id_index = feature->GetFieldIndex("osm_id");
            if (osm_id_index != -1) {
                int osm_road_type_index = feature->GetFieldIndex("highway");
                if (osm_road_type_index != -1) {
                    unsigned long long edge_id = strtoull(feature->GetFieldAsString(osm_id_index), nullptr, 10);
                    unique_ptr<Edge> new_edge = make_unique<Edge>(edge_id);
                    string road_type{feature->GetFieldAsString(osm_road_type_index)};
                    new_edge->type = road_type;
                    OGRLineString *road_geometry = feature->GetGeometryRef()->toLineString();
                    if (road_geometry) {
                        for (OGRPoint &p: road_geometry) {
                            unique_ptr<Node> new_node = make_unique<Node>(++node_id, p.getX(), p.getY());
                            new_edge->addNode(new_node.get());
                            mNode.insert({new_node->_id, move(new_node)});
                        }
                        new_edge->getNodes()->assignSpatialReference(dataref);
                        mEdge[edge_id] = move(new_edge);
                    }
                }
            }
            feature = roads_layer->GetNextFeature();
        }

        for (auto &e: mEdge) {
            e.second->setDistance();
        }
        return ret;
    }
    return -1;
}

OSMLoader *OSMRouteLoader::getLoader() const {
    return loader.get();
}

void OSMRouteLoader::setLoader(unique_ptr<OSMLoader> &value) {
    loader = move(value);
}

bool OSMRouteLoader::isFootEdge(const char *type) {
    string t{type};
    if (t == "steps" || t == "primary" || t == "primary_link"
            || t == "secondary" || t == "secondary_link" || t == "tertiary"
            || t == "tertiary_link" || t == "road" || t == "residential"
            || t == "living_street" || t == "footway" || t == "pedestrian"
            || t == "path" || t == "track" || t == "bridleway"
            || t == "unclassified")
        return true;
    return false;
}

bool OSMRouteLoader::isCarEdge(const char *type) {
    string t{type};
    if (t == "primary" || t == "primary_link" || t == "secondary"
            || t == "secondary_link" || t == "tertiary" || t == "tertiary_link"
            || t == "road" || t == "residential" || t == "living_street"
            || t == "bridleway" || t == "unclassified" || t == "motorway"
            || t == "motorway_link" || t == "trunk" || t == "trunk_link")
        return true;

    return false;
}

bool OSMRouteLoader::isCycleEdge(const char *type) {
    string t{type};
    if (t == "primary" || t == "primary_link" || t == "secondary"
            || t == "secondary_link" || t == "tertiary" || t == "tertiary_link"
            || t == "road" || t == "residential" || t == "living_street"
            || t == "cycleway" || t == "path" || t == "bridleway"
            || t == "unclassified")
        return true;

    return false;
}
/*
int OSMRouteLoader::isOneWay(const char *type) {
    int ret = 0;
    map<string, string>::iterator it = w->tags.find("oneway");
    if ((w->tags.find("junction") != w->tags.end())
            && ((w->tags.find("junction"))->second == "roundabout")) {
        ret = 1;
    }
    if (it != w->tags.end()) {
        if (it->second == "yes")
            ret = 1;
        else if (it->second == "-1")
            ret = -1;
    }

    return ret;
}/**/
/*
string OSMRouteLoader::edgeType(osm_way_t *w) {
    string ret = "Unknown";
    map<string, string>::iterator it = w->tags.find("highway");
    if (it != w->tags.end()) {
        ret = it->second;
    }
    return ret;
}
/**/

void OSMRouteLoader::convertGeogCS(OGRSpatialReference *ref)
{
    //for (auto it = vNode.begin(); it != vNode.end(); ++it) {
    for (auto &node: mNode) {
        if (node.second->getSpatialReference() == nullptr)
            node.second->assignSpatialReference(ref);
        else
            node.second->transformTo(ref);
    }
    //for (auto it=vEdge.begin(); it!=vEdge.end(); ++it) {
    for (auto &edge: mEdge) {
        if (edge.second->getNodes()->getSpatialReference() == nullptr)
            edge.second->getNodes()->assignSpatialReference(ref);
        else
            edge.second->getNodes()->transformTo(ref);
    }
}

void OSMRouteLoader::load(const char *filename) {
    string s{filename};
    int i = load(s);
}

void OSMRouteLoader::load(const string &filename) {
    load(filename.c_str());
}
