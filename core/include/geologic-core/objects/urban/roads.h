/**
 * \file	Roads.h
 */

#ifndef ROADS_H
#define ROADS_H

#include <ogr_spatialref.h>

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <set>

class RoadLoader;
class Node;
class Edge;
class GraphMobileObject;

using mapScore = std::map<Node *, double>;
using mapReverseScore = std::multimap<double, Node *>;
using mapPath = std::map<Node *, Node *>;

typedef mapScore::iterator mapScoreIt;
typedef mapReverseScore::iterator mapReverseScoreIt;
typedef mapPath::iterator mapPathIt;
typedef std::set<Edge *>::iterator setEdgeIt;

/*!
 * \brief The Roads class manages a road graphe with its logic
 */
class Roads {
    std::map<unsigned long long, std::unique_ptr<Node>> mNode; ///< Node map indexed by id
    std::map<unsigned long long, std::unique_ptr<Edge>> mEdge; ///< Edge map indexed by id
    std::unique_ptr<RoadLoader> loader; ///< The loader class dedicated to a given format.

public:
    Roads();
    void setLoader(RoadLoader *rl) {loader.reset(rl);}

    /*!
     * \brief load loads road data from a file
     * \param filename the path to the data source file
     */
    void load(const char *filename);

    /*!
     * \brief load loads road data from a file
     * \param filename the path to the data source file
     */
    void load(const std::string *filename);

    /*!
     * \brief addData loads road data from a file and merges
     * its content to the current road graphe
     * \param filename the path to the data source file
     */
    void addData(const char *filename);

    /*!
     * \brief addData loads road data from a file and merges
     * its content to the current road graphe
     * \param filename the path to the data source file
     */
    void addData(const std::string &filename);

    const auto &getmEdge()const {return mEdge;}
    const auto &getmNode()const {return mNode;}

    /*!
     * \brief roadInfo outputs various information about the roads loaded on the standard output
     */
    void roadInfo();

    /*!
     * \brief setGeogCS sets the data spatial reference
     * \param ref a pointer to the spatial reference
     */
    void setGeogCS(OGRSpatialReference *ref);

    /*!
     * \brief merge merges data from road graph r into this roads instance
     * \param r the roads to add to current instance.
     */
    void merge(Roads &r);

    // /////////////////////////////////////////
    // A* methods                             //
    // /////////////////////////////////////////
    /*!
     * \brief print_path prints the path resulting from A* to standard output
     */
    void print_path(GraphMobileObject *m);

    /*!
     * \brief rebuild_path builds the shortest path computed by A* for it to be displayed
     * \param path the path computed by A* algorithm
     */
    void rebuild_path(const std::map<unsigned long long, unsigned long long> &path, GraphMobileObject *m);

    /*!
     * \brief a_star searches the shortest path from source to destination defined by this class
     * attributes start_node and arrival_node
     * \param roads the road graphe (must contain start_node and arrival_node)
     */
    void a_star(GraphMobileObject *m);

};

#endif // ROADS_H
