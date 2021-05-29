#ifndef ROADLOADER_H
#define ROADLOADER_H

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <geologic-core/graphe/Node.h>
#include <geologic-core/graphe/Edge.h>
#include <ogr_spatialref.h>

/*!
 * \brief The RoadLoader interface provides the behaviour to load
 * road data from a source file. Its implementations must handle
 * the various data sources (OSM, SHP, etc.)
 */
class RoadLoader {
public:
    RoadLoader(OGRSpatialReference *ref);

    /*!
     * \brief load loads data from a file
     * \param filename the path to the data file
     */
    virtual void load(const char *filename) = 0;

    /*!
     * \brief load loads data from a file
     * \param filename the path to the data file
     */
    virtual void load(const std::string &filename) = 0;

    /*!
     * \brief getNodes transfers the nodes to its caller
     * \return the vector of nodes
     */
    std::map<unsigned long long, std::unique_ptr<Node> > getNodes();

    /*!
     * \brief getEdges transfers the edges to its caller
     * \return the vector of edges
     */
    std::map<unsigned long long, std::unique_ptr<Edge> > getEdges();

protected:
    std::map<unsigned long long, std::unique_ptr<Node> > mNode; ///< Road graph nodes loaded are put here
    std::map<unsigned long long, std::unique_ptr<Edge> > mEdge; ///< Road graph edges loaded are put here
    OGRSpatialReference *dataref;

};

#endif // ROADLOADER_H
