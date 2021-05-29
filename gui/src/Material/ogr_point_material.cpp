#include <Material/ogr_point_material.h>

ogr_point_material::ogr_point_material(float r, float g, float b, float a, float pt_size): Material("OGRPoint") {
    setDisplayMode(GL_POINT);
    setPointSize(pt_size);
    setLineWidth(pt_size);
    setColor("diffuse", QVector4D{r, g, b, a});
    setOption(GL_DEPTH_TEST, false);
}
