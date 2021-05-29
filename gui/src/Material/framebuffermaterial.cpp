#include "Material/framebuffermaterial.h"
#include <iostream>

#include <ResourceManagement/shadermanager.h>

using namespace std;

FramebufferMaterial::FramebufferMaterial(std::shared_ptr<Shader> shader):
    Material(shader, "Framebuffer")
{
//    setOption(GL_DEPTH_TEST, false);
    addUniform("u_type", 1);
    setDisplayMode(GL_FILL);
}


FramebufferMaterial::~FramebufferMaterial() {
}
