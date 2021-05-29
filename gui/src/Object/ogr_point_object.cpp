#include <Object/ogr_point_object.h>
#include <OpenGL/loadingmanager.h>

/*!
 * \brief ogr_point_object::ogr_point_object constructor
 * \param ogr_pt_data data that will be managed by the object
 * \param ogr_pt_mat material that will be managed by the object. Shall define point size and color for points, line width and color for lines.
 * \param v the view to be linked to (required for the geologic GUI framework to display points and lines)
 */
ogr_point_object::ogr_point_object(std::shared_ptr<Data> ogr_pt_data, std::shared_ptr<Material> ogr_pt_mat, View *v): ChildObject("OGRPoint") {
    m_render_layer = v->addRenderObject("ogr_points", this);
    setData(ogr_pt_data);
    setMaterial(ogr_pt_mat);
    LoadingManager::getInstance()->load(ogr_pt_data);
    ogr_pt_data->setPreloaded(true);
}
