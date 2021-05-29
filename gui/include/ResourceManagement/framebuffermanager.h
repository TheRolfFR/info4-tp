#pragma once

#include <ResourceManagement/resourcemanager.hpp>
#include <OpenGL/framebuffer.h>

class FramebufferManager: public ResourceManager<Framebuffer> {
    // needs to be friend in order to 
    // access the private constructor/destructor
    friend class ResourceManager<Framebuffer>; 
public:
    static FramebufferManager* getInstance(){
        static FramebufferManager* s_instance = new FramebufferManager();
        return s_instance;
    }

    void init();
    void load();

private:
    FramebufferManager();
    ~FramebufferManager();

};
