#pragma once

#include <Scene/view.h>
#include <memory>
#include <iostream>
#include <vector>
#include <geologic-core/core/geologic-launcher/CoordinateSystemManager.h>
#include <geologic-core/objects/geo/untemporal/Bbox.h>
#include <Data/signalmanager.h>

/*!
 * \class MovableView
 * \brief Class MovableView is an implementation of interface View.
 * A MovableView is a view in which the user can navigate.
 * This kind of view is used for instance for the main geographical view.
 * It provides especially the following features:
 * - zoom,
 * - rotation around x-axis,
 * - translation through mouse left button dragging.
 *
 * \see View
 */
class MovableView: public View {
private:
    Bbox m_view_bbox;                                 ///< View bounding box in data SRS
    Bbox m_data_bbox;                                 ///< View bounding box in view SRS
    OGRPoint m_corner_dataref;
    OGRPoint m_corner_viewref;
    OGRPoint m_center_dataref;                        ///< Coordinates where the user actually looks at, in data SRS
    OGRPoint m_center_viewref;                        ///< Coordinates where the user actually looks at, in view SRS
    QVector2D m_viewCenter;

	bool m_perspective;
    double m_z_clipping_min, m_z_clipping_max;          ///< Z Clipping plans (eventually to be computed)
    int m_zoom;                                       ///< Used for zoom, based on OSM zoom levels
    const int m_max_scale = 18;                       ///< Zoom limit (18 for now)
    double m_x_rotation;                              ///< View X rotation (from 0.0 to 75.0)
    double m_z_rotation;                              ///< View Z rotation (no limit)

public:

    /*!
     * \brief Sets current View view center (i.e. where the user is looking at)
     * \param x in viewRef SRS
     * \param y in viewRef SRS
     */
    //virtual void setViewCenter(double x, double y);

    /*!
     * \brief Moves the current View center from a relative amount.
     * Updates the View center based on a relative offset.
     * \param x_offset the horizontal offset in viewRef SRS.
     * \param y_offset the vertical offset in viewRef SRS.
     */
    virtual void moveViewCenter(double x_offset, double y_offset);

    virtual void moveViewCenter(int x_offset_px, int y_offset_px);

    /*!
     * \brief setCenter modifies the view center.
     * In particular, it sets the center in both data and view references,
     * and recomputes the bounding box parameters.
     * \param p is the new center.
     */
    virtual void setCenter(const OGRPoint &p);

    MovableView(): View(), m_perspective(false), m_x_rotation(0.0), m_z_rotation(0.0) {}

    /*!
     * \brief Destructor.
     * Does not do anything currently.
     */
    ~MovableView();

    virtual void setZoom(int z) {m_zoom = z; updateView();}
    virtual int getZoom() {return m_zoom;}

    /*!
     * \brief Called when a zoom in action is triggered in GLDisplay.
     */
    virtual void zoomIn();

    /*!
     * \brief Called when a zoom out action is triggered in GLDisplay.
     */
    virtual void zoomOut();

    /*!
     * \brief Computes the 2D GL Ortho boundaries.
     * It is used to compute the boundaries without changing the image aspect ratio.
     * It uses footprint size and screen size to compute the boundaries.
     */
    virtual void updateView();

    /*!
     * \brief Gets the minimum values of View boundaries.
     * \return x and y minimum value as a std::pair of double.
     */
    virtual std::pair<double, double> getMinBoundaries();

    double getViewXMin() {return m_view_bbox.minx;}
    double getViewXMax() {return m_view_bbox.maxx;}
    double getViewYMin() {return m_view_bbox.miny;}
    double getViewYMax() {return m_view_bbox.maxy;}

    double getDataXMin() {return m_data_bbox.minx;}
    double getDataXMax() {return m_data_bbox.maxx;}
    double getDataYMin() {return m_data_bbox.miny;}
    double getDataYMax() {return m_data_bbox.maxy;}

    Bbox &getDataBBox() {return m_data_bbox;}
    Bbox &getViewBBox() {return m_view_bbox;}

    const OGRPoint &getCenterInDataRef() const { return m_center_dataref; }
    const OGRPoint &getCenterInViewRef() const { return m_center_viewref; }

    virtual void setGeoRefs();

    double getXrotation() {return m_x_rotation;}
    double getZrotation() {return m_z_rotation;}
    virtual void reinitializeAngles() {m_x_rotation = m_z_rotation = 0.0;     updateView();}
    /*!
     * \brief Modifies the View angle.
     * It modifies the View rotation angle.
     * \param mod_angle The new rotation angle value.
     */
    virtual void modAngle(double mod_angle);

    /*!
     * \brief Modifies the View angle.
     * It modifies the View rotation angle.
     * \param mod_angle The new rotation angle value.
     */
    virtual void modZAngle(double mod_angle);


	virtual void switchProjection() { m_perspective = !m_perspective; updateView(); };

    /**/
};
