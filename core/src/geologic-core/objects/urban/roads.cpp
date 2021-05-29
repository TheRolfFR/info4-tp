/**
 * \file	Roads.cpp
 * \class	Roads
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Roads object
 *
 * Methods of Roads object
 */

#include <iostream>
#include <algorithm>
#include <exception>
#include "geologic-core/objects/urban/roads.h"
#include "geologic-core/graphe/Node.h"
#include "geologic-core/graphe/Edge.h"
#include "geologic-core/objects/urban/roadloader.h"
#include <geologic-core/objects/dynamic/GraphMobileObject.h>

using namespace std;

Roads::Roads() {}

void Roads::load(const char *filename) {
    if (loader != nullptr) {
        loader->load(filename);
        mNode = loader->getNodes();
        mEdge = loader->getEdges();
    }
}

void Roads::load(const string *filename) {
    load(filename->c_str());
}

void Roads::addData(const char *filename __attribute__((unused))) {
    // Load data, then merge the graphes
}

void Roads::addData(const string &filename) {
    addData(filename.c_str());
}

void Roads::roadInfo() {
    cout << "Node count: " << mNode.size() << "\nEdge count: " << mEdge.size() << endl;
}

void Roads::setGeogCS(OGRSpatialReference *ref) {
    for (auto &node: mNode) {
        node.second->assignSpatialReference(ref);
    }
    for (auto &edge: mEdge) {
        edge.second->getNodes()->assignSpatialReference(ref);
    }
}

void Roads::merge(Roads &r) {
    // Merge nodes (insert nodes from r.vNode to this->vNode if not exist in this->vNode)
    for (auto &node: r.mNode) {
        if (mNode.find(node.first) == mNode.end()) {
            mNode[node.first] = move(node.second);
        }
    }

    // Merge edges (insert edges from r.vEdge to this->vEdge if not exist in this->vEdge)
    for (auto &edge: r.mEdge) {
        if (mEdge.find(edge.first) == mEdge.end()) {
            mEdge[edge.first] = move(edge.second);
        }
    }

    // Clear r.vNode, r.vEdge
    r.mNode.clear();
    r.mEdge.clear();
}

void Roads::print_path(GraphMobileObject *m) {
    auto &path_nodes = m->getPathnode();
    auto &path_edges = m->getPathedge();
    unsigned int i;
    if (path_nodes.size() != path_edges.size() + 1) {
        cout << "Wrong path data" << endl;
    } else {
        for (i = 0  ; i < path_edges.size() ; ++i) {
            cout << "(" << path_nodes[i]->getX() << ";" << path_nodes[i]->getY() << ") -> ";
        }
        cout << "(" << path_nodes[i]->getX() << ";" << path_nodes[i]->getY() << ")" << endl;
    }
}

void Roads::rebuild_path(const map<unsigned long long, unsigned long long> &path, GraphMobileObject *m) {
    auto &path_nodes = m->getPathnode();
    auto &path_edges = m->getPathedge();
    unsigned int i;
    double d;
    vector<Node *> nodes;
    auto mpit = path.find(m->getArrivalnode()->_id);
    map<double, Edge *> possible_edges;

    // Debugging
    /*/
    for (auto &entry: path) {
        cout << entry.second << " -> " << entry.first << endl;
    }
    //*/

    // rebuild path from map path (children/parent)
    nodes.push_back(m->getArrivalnode());
    while (mpit != path.end()) {
        try {
            nodes.push_back(mNode.at(mpit->second).get());
            mpit = path.find(mpit->second);
        } catch (exception &ex) {
            cout << ex.what() << ": " << mpit->second << endl;
        }
    }

    for (i=nodes.size(); i>0; --i) {
        // fill path_nodes
        if (i != nodes.size())
            path_nodes.push_back(nodes[i - 1]);

        // fill path_edges
        if (i > 1) {
            // Find all traversable edges from nodes[i-1] to nodes[i-2]
            for (const unsigned long long edge_id: nodes[i - 1]->sedge) {
                // Chose of good node extremety (last or first)
                try {
                    Edge *e = mEdge.at(edge_id).get();
                    unsigned long long other_node = (e->last() == nodes[i - 1]->_id)
                            ? e->first()
                            : e->last();
                    // if it is a good edge and we can pass through
                    if (other_node == nodes[i - 2]->_id) {
                        d = m->traverse(e, other_node, 0);
                        if (d > 0)
                            possible_edges[d] = e;
                    }
                } catch (exception &ex) {
                    cout << ex.what() << ": " << edge_id << endl;
                }
            }
            // Use first (shortest one) to fill path_edges
            path_edges.push_back((possible_edges.begin())->second);
            // Clear map
            possible_edges.clear();
        }
    }
    nodes.clear();
}

void Roads::a_star(GraphMobileObject *m) {
    set<unsigned long long> closedset;                     // The set of nodes already evaluated
    set<unsigned long long> openset;                       // The set of nodes to be evaluated

    map<unsigned long long, double> f_score;               // Map of estimated total distance from start to goal (g + h)
    map<unsigned long long, double> g_score;               // Map of cost from start along optimal path
    map<unsigned long long, unsigned long long> path;      // map historical path (children nodes, best parent nodes)

    double dist_edge, dist_eval;
    unsigned long long current, neighbor;

    // Initialize openset and map of distance (closedset is empty)
    openset.insert(m->getStartnode()->_id);
    g_score[m->getStartnode()->_id] = 0;
    f_score[m->getStartnode()->_id] = m->getStartnode()->straightDistance(m->getArrivalnode());

    while (!openset.empty()) {
        // Choose the candidate with shortest heuristic distance
        auto current_it = min_element(begin(openset), end(openset), [&f_score](const unsigned long long &n1, const unsigned long long &n2) {
            return f_score[n1] < f_score[n2];
        });
        current = *current_it;

        // If candidate is destination, end of algorithm
        if (current == m->getArrivalnode()->_id) {
            rebuild_path(path, m);
            return ;
        }

        // Update open and closed list => Switch current from openset to closedset
        openset.erase(current);
        closedset.insert(current);

        // Add new adjacent nodes to openset explorating all edges of current node
        for (auto e: mNode.at(current)->sedge) {
            // choose good node (first or last) of explorated edge depending of who is the current node...
            try {
                Edge* edge = mEdge.at(e).get();
                neighbor = (edge->last() == current) ? edge->first() : edge->last();
//                cout << "traverse edge " << edge->id << " to node " << mNode.at(neighbor)->_id << endl;
                dist_edge = m->traverse(edge, neighbor, 0);
//                cout << "FINtraverse" << dist_edge << endl;

                // If edge can not be passed through (not authorized), we skip this edge, no neighbor to be evaluated
                if (dist_edge == -1)
                    continue;

                // If not, it is possible a neighbor, start of this evaluation (current cost + new cost)
                dist_eval = g_score[current] + dist_edge;   //
                //debug("Traverse: " + to_string(dist_edge));

                // We look for this neighbor in the closed list (elements already explorated)
                auto csit = closedset.find(neighbor);

                // If already explorated with a better cost, we skip...
                if (csit != end(closedset) && g_score.at(neighbor) <= dist_eval)
                    continue;

                // We look for this neighbor in the open list (elements to be explorated in priority)
                auto osit = openset.find(neighbor);

                // If not found or already present in the open list with a worse cost
                if (osit == end(openset) || g_score.at(neighbor) > dist_eval) {
                    // update/insert path
                    path[neighbor] = current;
                    // update/insert new cost
                    g_score[neighbor] = dist_eval;
                    // update/insert totale distance (G cost + H heuristic)
                    f_score[neighbor] = g_score[neighbor] + mNode.at(neighbor)->straightDistance(m->getArrivalnode());
                    // If realy not found, case insert (if advised for performance)
                    if (osit == openset.end())
                        openset.insert(neighbor);
                }
            }
            catch (exception &e) {
                cout << e.what() << endl;
            }
        }
    }
}
