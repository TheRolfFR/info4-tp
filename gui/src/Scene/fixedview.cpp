#include "Scene/fixedview.h"
#include <iostream>
#include <QtOpenGL/QtOpenGL>
#include <Simulation/simulationclock.h>
#include <geologic-core/utils/customToolbox.h>
#include <geologic-core/algorithms/geoMetrics/geoMetrics.h>
#include <geologic-core/core/geologic-launcher/CoordinateSystemManager.h>

using namespace std;

FixedView::FixedView() : View() {
}


FixedView::~FixedView() {
}


void FixedView::updateView() {
	m_projection.setToIdentity();
	m_view.setToIdentity();

    m_projection.ortho(0, m_screen_width, 0, m_screen_height, -200000000, 200000000);
}
