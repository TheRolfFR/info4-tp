#pragma once

#include <QMatrix4x4>
#include <Object/rootobject.h>
#include <Scene/layer.h>

class BackgroundObject;

/*!
 * \interface View
 * \brief Interface View manages a GLDisplay subsection with a variety of Layers.
 *
 * Interface View is embedded to a GLDisplay and defines a view (general view, minimap, etc.)
 * View members are used to define
 * the View properties (footprint, etc.) and are in charge of a GL viewport.
 *
 * \see GLDisplay
 */
class View {
protected:
    bool m_visible;       ///< Defines if the whole view is visible
                        ///< true if displayed
                        ///< false otherwise
    GLsizei m_screen_width;	///< Screen/frame width, pixels
    GLsizei m_screen_height;	///< Screen/frame height, pixels
    GLint m_screen_left;
    GLint m_screen_top;

    bool m_resized;       ///< Boolean value indicating when the viewport must be redeclared
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;

    std::map<std::string, Layer*> m_layers;
    std::vector<Layer*> m_render_tree;
    std::unique_ptr<RootObject> m_update_tree;

    BackgroundObject* m_background;

public:
    View();
    virtual ~View();
    int getScreenWidth() const {return m_screen_width;};
    int getScreenHeight() const {return m_screen_height;};

    /*!
     * \brief Updates the whole tree 
     * This method is called by the scene manager when it requires to update the tree.
     */
    virtual void update(double t = 0);

    void initViewport();

    /*!
     * \brief Draws the View when no animation is playing.
     * This method is called by the scene manager when it requires to refresh itself.
     * Does not do anything if attribute visible is set to false.
     */
    void draw();

    void drawCheckboxes(QWidget* tab, QLayout* layout);

    /*!
     * \brief Adds an object to the tree root. 
     */
    void addObject(Object* obj);

    /*!
     * \brief Add a ChildObject to the render tree
     * \returns the parent node of the added object
     */
    Layer* addRenderObject(std::string layer, ChildObject* obj);
    
    void addLayer(std::string layer);
    
    void addLayer(std::string layer, Layer* l);

    /*!
     * \brief Sets current View visible.
     * It sets the visible attribute to true, so the View content is displayed.
     */
    void setVisible() {m_visible = true;}

    /*!
     * \brief Sets current View invisible.
     * It sets the visible attribute to false, so the View is no longer displayed.
     */
    void setHidden() {m_visible = false;}

    /*!
     * \brief toggles current View visible attribute.
     * It inverses the current View visibility state.
     */
    void toggleVisibility() {m_visible = !m_visible;}

    void setPosition(GLint left, GLint top);

    /*!
     * \brief Informs current View of its parent GLDisplay size.
     * Triggered by parent GLDisplay is resizeGL.
     * \param width The width (pixels) of the parent GLDisplay
     * \param height The height (pixels) of the parent GLDisplay
     */
    void setSize(GLsizei width, GLsizei height);

    /*!
     * \brief Queries visibility status of current View.
     * \return true if visible, false else.
     */
    bool isVisible() {return m_visible;}

    /*!
     * \brief resize computes new view parameters for OpenGL display.
     * Needed by all types of views
     */
    virtual void updateView() = 0;

    RootObject* getRoot() { return m_update_tree.get(); };

};
