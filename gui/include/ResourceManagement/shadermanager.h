#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <ResourceManagement/resourcemanager.hpp>
#include <OpenGL/shader.h>


class ShaderManager: public ResourceManager<Shader> {
    // needs to be friend in order to 
    // access the private constructor/destructor
    friend class ResourceManager<Shader>; 
public:
    static ShaderManager* getInstance(){
        static ShaderManager* s_instance = new ShaderManager();
        return s_instance;
    }

    void init();
    void load();

    std::shared_ptr<Shader> importFromFile(std::string id);

private:
    ShaderManager();
    ~ShaderManager();

};

#endif // SHADERMANAGER_H
