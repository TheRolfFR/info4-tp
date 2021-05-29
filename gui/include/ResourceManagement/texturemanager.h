#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <ResourceManagement/resourcemanager.hpp>
#include <OpenGL/texture.h>


class TextureManager: public ResourceManager<Texture> {

public:
    static TextureManager* getInstance(){
        static TextureManager* s_instance = new TextureManager();
        return s_instance;
    }

    void init();
    void load();

    std::shared_ptr<Texture> importFromFile(std::string id);

private:
    TextureManager();
    ~TextureManager();

};

#endif // TEXTUREMANAGER_H
