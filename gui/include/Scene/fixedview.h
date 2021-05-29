#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include <ogr_geometry.h>
#include <memory>
#include <utility>
#include <iostream>
#include <Scene/view.h>
#include <vector>


/*!
 * \class FixedView
 * \brief Class FixedView implements interface View.
 *
 * It is a static view that cannot be moved, nor zoomed, nor rotated.
 * It is typically used in clock display and minimap.
 *
 * \see View
 */
class FixedView: public View {
public:

    /*!
     * \brief Constructor.
     * Initializes base View properties
     */
    FixedView();

    /*!
     * \brief Destructor
     *
     * Does not do anything currently
     */
    virtual ~FixedView();

    virtual void updateView();
};
