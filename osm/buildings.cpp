#include "buildings.h"
#include <osmloader.h>
#include <string>
#include <Common/color.h>
#include <vector>

#include <iostream>

using namespace std;

Buildings::Buildings(OGRSpatialReference *v): _viewref(v) {
    _georef.importFromEPSG(4326);
}

void Buildings::load(const char *filename) {
    OSMLoader loader;
    string f(filename);
    loader.loadOSMfile(f);
/*    const osm_node_map_t& nodes = loader.getmOSMnode();
    const osm_way_map_t& ways = loader.getmOSMway();

    for (const auto &building: ways) {
        osm_way_t *border = building.second;
        OGRLineString *shape = new OGRLineString;
        bool invalid = false;
        for (unsigned int i=0; i<border->vnodes_ref.size()-1; ++i) {
            try {
                osm_node_t *node = nodes.at(border->vnodes_ref[i]);
                shape->addPoint(node->longitude, node->latitude);
            } catch(out_of_range &e) {
                invalid = true;
            }
        }
        if (!invalid) {
            _bld_borders.addGeometryDirectly(shape);
        }
    }

    _bld_borders.assignSpatialReference(&_georef);*/
}

void Buildings::draw() {
    /*
    OGRCoordinateTransformation *transform = OGRCreateCoordinateTransformation(&_georef, _viewref);
    if (!transform) // Transform error: cannot convert therefore display
        return;

    Color bgcolor{0.75, 0.75, 0.75, 0.6};
    if (_surface_list == 0) {
        _surface_list = glGenLists(1);
        if (_surface_list == 0)
            return;

        glNewList(_surface_list, GL_COMPILE);
        ZoneDisplayer::draw(&_bld_borders, &bgcolor, _viewref);
        glEndList();
    }
    if (_surface_list != 0) {
        glColor4d(bgcolor.red, bgcolor.green, bgcolor.blue, bgcolor.alpha);
        glCallList(_surface_list);
    }

    Color bordercolor{1.0, 1.0, 1.0, 1.0};
    if (_display_list == 0) {
        _display_list = glGenLists(1);
        if (_display_list == 0) // Resource error?
            return;
        // Prepare data to display
        vector<double> xs;
        vector<double> ys;
        vector<double> zs;
        vector<int> sizes;

        // Extract all coordinates
        int count_bld = _bld_borders.getNumGeometries();
        for (int i=0; i<count_bld; ++i) {
            OGRLineString *brdr = reinterpret_cast<OGRLineString *>(_bld_borders.getGeometryRef(i));
            xs.insert(xs.begin(), brdr->getNumPoints(), 0.0);
            ys.insert(ys.begin(), brdr->getNumPoints(), 0.0);
            zs.insert(zs.begin(), brdr->getNumPoints(), 0.0);
            sizes.insert(sizes.begin(), 1, brdr->getNumPoints());
            // brdr->getPoints(xs.data(), 1, ys.data(), 1, zs.data(), 1); Weird behaviour: doesn't work
            for (int j=0; j<brdr->getNumPoints(); ++j) {
                OGRPoint p;
                brdr->getPoint(j, &p);
                xs[j] = p.getX();
                ys[j] = p.getY();
                zs[j] = p.getZ();
            }
        }

        // Convert coordinates
        transform->Transform(xs.size(), xs.data(), ys.data(), zs.data());
        cout << "Total points: " << xs.size() << endl;
        cout << "Buildings count: " << sizes.size() << endl;
        cout << "First point: " << xs[0] << ", " << ys[0] << ", " << zs[0] << endl;

        // Display
        int glob_pos = 0;
        glNewList(_display_list, GL_COMPILE);
        for (unsigned int i=0; i<sizes.size(); ++i) {
            glBegin(GL_LINE_LOOP);
            for (int j=glob_pos; j<glob_pos+sizes[i]; ++j) {
                glVertex3d(xs[j], ys[j], zs[j]);
            }
            glob_pos += sizes[i];
            glEnd();
        }
        glEndList();
    }
    if (_display_list != 0) {
        glColor4d(bordercolor.red, bordercolor.green, bordercolor.blue, bordercolor.alpha);
        glLineWidth(1.0);
        glCallList(_display_list);
    }
*/
}

void Buildings::draw(unsigned long long t) {
    draw();
}
