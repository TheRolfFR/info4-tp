#include <Scene/movableview.h>

#include <iostream>
#include <cmath>
#include <cstdio>
#include <Common/color.h>
#include <geologic-core/utils/customToolbox.h>
#include <geologic-core/algorithms/geoMetrics/geoMetrics.h>
#include <geologic-core/core/geologic-launcher/CoordinateSystemManager.h>

#include <QtOpenGL/QtOpenGL>
#define PI 3.14159265

using namespace std;

void MovableView::zoomIn() {
    customToolbox::start("MovableView::zoomIn");
    m_zoom++;
    if (m_zoom > 18)
        m_zoom = 18;
    cout << "Zoom: " << m_zoom << endl;
    updateView();
    customToolbox::end("MovableView::zoomIn");
}


void MovableView::zoomOut() {
    customToolbox::start("MovableView::zoomOut");
    m_zoom--;
    if (m_zoom < 0)
        m_zoom = 0;
    cout << "Zoom: " << m_zoom << endl;
    updateView();
    customToolbox::end("MovableView::zoomOut");
}


MovableView::~MovableView() {
    //cout << "MovableView::~MovableView()" << endl;
}


void MovableView::moveViewCenter(double x_offset, double y_offset) {
    customToolbox::start("MovableView::moveViewCenter(double)");
    CoordinateSystemManager* geoRefs = CoordinateSystemManager::getInstance();
    if (geoRefs == nullptr) {
        customToolbox::end("MovableView::moveViewCenter(double)");
        return;
    }
    OGRPoint p{x_offset + m_center_dataref.getX(), y_offset + m_center_dataref.getY()};
    p.assignSpatialReference(geoRefs->getDataRef());
    setCenter(p);
    customToolbox::end("MovableView::moveViewCenter(double)");
}


void MovableView::moveViewCenter(int x_offset_px, int y_offset_px) {
    customToolbox::start("MovableView::moveViewCenter(int)");
    CoordinateSystemManager* geoRefs = CoordinateSystemManager::getInstance();
    if (geoRefs == nullptr) {
        customToolbox::end("MovableView::moveViewCenter(int)");
        return;
    }

    QMatrix4x4 view;
    view.rotate(-m_x_rotation, QVector3D(1.0, 0.0, 0.0));
    view.rotate(-m_z_rotation, QVector3D(0.0, 0.0, 1.0));

    QVector4D offset = view * QVector4D(x_offset_px, y_offset_px, 0, 1.0);
    double x_percent = (double) offset.x() / (double) m_screen_width;
    double y_percent = (double) offset.y() / (double) m_screen_height;
    double x_offset = x_percent * (m_data_bbox.maxx - m_data_bbox.minx);
    double y_offset = y_percent * (m_data_bbox.maxy - m_data_bbox.miny);


    moveViewCenter(x_offset, y_offset);
    customToolbox::end("MovableView::moveViewCenter(int)");
}


std::pair<double, double> MovableView::getMinBoundaries() {
    return pair<double, double>{m_view_bbox.minx, m_view_bbox.miny};
}


void MovableView::setGeoRefs() {
    customToolbox::start("MovableView::setGeoRefs");
    CoordinateSystemManager* geoRefs = CoordinateSystemManager::getInstance();
    if (m_center_dataref.getSpatialReference() == nullptr) {
        m_center_dataref.assignSpatialReference(geoRefs->getDataRef());
        //customToolbox::message("No spatial reference.\n");
    } else if (m_center_dataref.getSpatialReference()->IsSameGeogCS(geoRefs->getDataRef()) == 0) {
        //customToolbox::message("Different spatial reference.\n");
        m_center_dataref.transformTo(geoRefs->getDataRef());
    }
    m_center_viewref = m_center_dataref;
    m_center_viewref.transformTo(geoRefs->getViewRef());
    updateView();
    customToolbox::end("MovableView::setGeoRefs");
}


void MovableView::updateView() {
    CoordinateSystemManager* geoRefs = CoordinateSystemManager::getInstance();
    if (geoRefs == nullptr) {
        customToolbox::end("MovableView::updateView [error]");
        return;
    }

//    OGRPoint origin;
    m_data_bbox.setWGS84Bbox(&m_center_dataref, m_screen_width, m_screen_height, m_zoom);

    OGRPoint data_min(m_data_bbox.minx, m_data_bbox.miny);
    OGRPoint data_max(m_data_bbox.maxx, m_data_bbox.maxy);

    data_min.assignSpatialReference(geoRefs->getDataRef());
    data_max.assignSpatialReference(geoRefs->getDataRef());

    OGRPoint view_min = data_min;
    OGRPoint view_max = data_max;

    view_min.transformTo(geoRefs->getViewRef());
    view_max.transformTo(geoRefs->getViewRef());

    m_view_bbox.set(min(view_min.getX(), view_max.getX()), max(view_min.getX(), view_max.getX()),
                    min(view_min.getY(), view_max.getY()), max(view_min.getY(), view_max.getY()));

//    cout << "BBox: " << m_view_bbox << endl;

	m_projection.setToIdentity();
	m_view.setToIdentity();
	if(m_perspective) {
		float fov = 90;
		double distance = ((m_view_bbox.maxx - m_view_bbox.minx)/2)/tan((fov/2.0)/180.0*PI);
		m_projection.perspective(fov, (float)m_screen_width/m_screen_height, 1, 200000000);
		m_view.lookAt(	QVector3D(m_center_viewref.getX(), m_center_viewref.getY(), 1000), 
						QVector3D(m_center_viewref.getX(), m_center_viewref.getY(), 0),
						QVector3D(0, 1, 0));
		m_view.translate(0, 0, -distance);
	} else {
		m_projection.ortho(m_view_bbox.minx, m_view_bbox.maxx, m_view_bbox.miny, m_view_bbox.maxy, -200000000, 200000000);
		m_projection.translate(-m_center_viewref.getX(), -m_center_viewref.getY());
		m_view.translate(m_center_viewref.getX(), m_center_viewref.getY());
	}

    m_view.translate(m_center_viewref.getX(), m_center_viewref.getY());
    m_view.rotate(m_x_rotation, QVector3D(1.0, 0.0, 0.0));
    m_view.rotate(m_z_rotation, QVector3D(0.0, 0.0, 1.0));
    m_view.translate(-m_center_viewref.getX(), -m_center_viewref.getY());
}


void MovableView::setCenter(const OGRPoint &p) {
    CoordinateSystemManager* geoRefs = CoordinateSystemManager::getInstance();
    if (geoRefs == nullptr) {
        customToolbox::end("MovableView::setCenter");
        return;
    }
    m_center_dataref = p;
    if (m_center_dataref.getSpatialReference() == nullptr)
        m_center_dataref.assignSpatialReference(geoRefs->getDataRef());
    if (m_center_dataref.getSpatialReference()->IsSameGeogCS(geoRefs->getDataRef()) != 0) {
        m_center_viewref = m_center_dataref;
        m_center_viewref.transformTo(geoRefs->getViewRef());
        updateView();
    } else {
        cerr << "Cannot change view center: Spatial Reference mismatch." << endl;
    }
}


void MovableView::modAngle(double mod_angle) {
    m_x_rotation += mod_angle;
    if (m_x_rotation < -75.0) m_x_rotation = -75.0;
    if (m_x_rotation > 0.0) m_x_rotation = 0.0;
	updateView();
}


void MovableView::modZAngle(double mod_angle) {
    m_z_rotation += mod_angle;
	updateView();
}
