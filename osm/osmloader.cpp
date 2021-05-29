#include "osmloader.h"

#include <geologic-core/utils/customToolbox.h>
#include <iostream>
#include <cstdio>
#include <clocale>

using namespace std;

OSMLoader::OSMLoader() {}

OSMLoader::~OSMLoader() {
    GDALClose(_my_data);
}
/*
const osm_node_map_t& OSMLoader::getmOSMnode() const {
    return mOSMnode;
}

const osm_way_map_t& OSMLoader::getmOSMway() const {
    return mOSMway;
}

const osm_relation_map_t &OSMLoader::getmOSMrelation() const {
    return mOSMrelation;
}

int OSMLoader::loadOSMnode(const void *user_data, const readosm_node *node) {
    osm_node_t *recnode = new osm_node_t;
    osm_node_map_t &m_node = reinterpret_cast<const OsmPointer *>(user_data)->m_node;

    recnode->id = node->id;
    recnode->latitude = node->latitude;
    recnode->longitude = node->longitude;

    for (int i = 0; i < node->tag_count; i++) {
        recnode->tags[string(node->tags[i].key)] = string(node->tags[i].value);
    }

    // Fill the Node * field
    m_node[node->id] = recnode;
    return READOSM_OK;
}

int OSMLoader::loadOSMway(const void *user_data, const readosm_way *way) {
    osm_way_t *recway = new osm_way_t;
    osm_way_map_t &m_way = reinterpret_cast<const OsmPointer *>(user_data)->m_way;

    recway->id = way->id;

    for (int i = 0; i < way->node_ref_count; ++i)
        recway->vnodes_ref.push_back(way->node_refs[i]);

    for (int i = 0; i < way->tag_count; ++i) {
        recway->tags[string(way->tags[i].key)] = string(way->tags[i].value);
    }

    // Fill the Way * field
    m_way[way->id] = recway;
    return READOSM_OK;
}

int OSMLoader::loadOSMrelation(const void *user_data, const readosm_relation *relation) {
    osm_relation_t *recrelation = new osm_relation_t;
    osm_relation_map_t &m_relation = reinterpret_cast<const OsmPointer *>(user_data)->m_relation;

    recrelation->id = relation->id;

    for (int i=0; i<relation->member_count; ++i) {
        recrelation->members.push_back(osm_member_t{relation->members[i].member_type, relation->members[i].id, relation->members[i].role});
    }

    for (int i=0; i<relation->tag_count; ++i) {
        recrelation->tags[relation->tags->key] = relation->tags->value;
    }

    m_relation[relation->id] = recrelation;
    return READOSM_OK;
}
*/

int OSMLoader::loadOSMfile(std::string &filename) {

    // WARNING : Please check local LC_NUMERIC value => setlocale(LC_NUMERIC, "C") needed to handle . or , numeric separator in file

    setlocale(LC_NUMERIC, "C");
    GDALAllRegister();

    _my_data = nullptr;
    char **options = nullptr;
    options = CSLAddNameValue(options, "USE_CUSTOM_INDEXING", "NO");
    _my_data = (GDALDataset *) GDALOpenEx(filename.c_str(), GDAL_OF_VECTOR, NULL, options, NULL);
    CSLDestroy(options);

    if (!_my_data)
        return -1;
    return 0;
/*
    int ret;
    const void *osm_handle;
    const char *file = filename.c_str();

    ret = readosm_open(file, &osm_handle);

    if (ret != READOSM_OK) {
        cout << "Error while opening OSM file: " << filename
                << " with error code: " << ret << endl;
        return ret;
    }

    OsmPointer internal_structs = { mOSMnode, mOSMway, mOSMrelation };
    ret = readosm_parse(osm_handle, (const void *) &internal_structs,
            loadOSMnode, loadOSMway, loadOSMrelation);

    if (ret != READOSM_OK) {
        cout << "Error while parsing OSM file: " << filename
                << " with error code: " << ret << endl;
        return ret;
    }

    readosm_close(osm_handle);
    return READOSM_OK;*/
}

int OSMLoader::loadOSMfile(const char *filename) {
    string f{filename};
    return loadOSMfile(f);
}

/*
void OSMLoader::clearOSMdata() {
    for (pair<long long, osm_way_t *> elt: mOSMway) {
        delete elt.second;
    }
    for (pair<long long, osm_node_t *> elt: mOSMnode) {
        delete elt.second;
    }

    for (pair<long long, osm_relation_t *> elt: mOSMrelation) {
        delete elt.second;
    }

    mOSMnode.clear();
    mOSMway.clear();
    mOSMrelation.clear();
}
*/
