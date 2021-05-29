#ifndef OSMLOADER_H
#define OSMLOADER_H

//#include <readosm.h>

#include <gdal/ogrsf_frmts.h>

#include <string>
#include <vector>
#include <map>
/*
struct osm_node_struct {
    long long id;
    double latitude;
    double longitude;
    std::map<std::string, std::string> tags;
};
typedef struct osm_node_struct osm_node_t;

struct osm_way_struct {
    long long id;
    std::map<std::string, std::string> tags;
    std::vector<long long> vnodes_ref;
};
typedef struct osm_way_struct osm_way_t;

struct osm_member_struct {
    int member_type; ///< can be one of: READOSM_MEMBER_NODE, READOSM_MEMBER_WAY or READOSM_MEMBER_RELATION
    long long id; ///< ID-value identifying the referenced object
    std::string role; ///< intended role for this reference
};
using osm_member_t = struct osm_member_struct;

struct osm_relation_struct {
    long long id;
    std::vector<osm_member_t> members;
    std::map<std::string, std::string> tags;
};
using osm_relation_t = struct osm_relation_struct;

typedef std::map<long long, osm_node_t *> osm_node_map_t;
typedef std::map<long long, osm_node_t *>::iterator osm_node_map_iterator;

typedef std::map<long long, osm_way_t *> osm_way_map_t;
typedef std::map<long long, osm_way_t *>::iterator osm_way_map_iterator;

using osm_relation_map_t = std::map<long long, osm_relation_t *>;

typedef struct {
    osm_node_map_t &m_node;
    osm_way_map_t &m_way;
    osm_relation_map_t &m_relation;
} OsmPointer;
*/
class OSMLoader {
private:
    GDALDataset *_my_data = nullptr;

public:
    OSMLoader();
    virtual ~OSMLoader();
    int loadOSMfile(const char *filename);
    int loadOSMfile(std::string &filename);
    GDALDataset *get_dataset() {return _my_data;}

//    const osm_node_map_t& getmOSMnode() const;
//    const osm_way_map_t& getmOSMway() const;
//    const osm_relation_map_t& getmOSMrelation() const;

protected:
//    osm_node_map_t mOSMnode;
//    osm_way_map_t mOSMway;
//    osm_relation_map_t mOSMrelation;
//    void clearOSMdata();

//private:
//    static int loadOSMnode(const void *user_data, const readosm_node *node);
//    static int loadOSMway(const void *user_data, const readosm_way *way);
//    static int loadOSMrelation(const void *user_data, const readosm_relation *relation);
};

#endif // OSMLOADER_H
