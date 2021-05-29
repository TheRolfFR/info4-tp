#ifndef TILETEXTUREMANAGER_H
#define TILETEXTUREMANAGER_H

#include <ResourceManagement/resourcemanager.hpp>
#include <OpenGL/texture.h>


class TileTextureManager: public ResourceManager<Texture> {
    // needs to be friend in order to 
    // access the private constructor/destructor
    friend class ResourceManager<Texture>; 
private:
    std::string m_baseUrl;

public:
    static TileTextureManager* getInstance(){
        static TileTextureManager* s_instance = new TileTextureManager();
        return s_instance;
    }

    virtual void flush() override{
        m_library.clear();
    }

    void init(std::string baseUrl);
    void load(std::string baseUrl);

    std::shared_ptr<Texture> importFromFile(std::string id);
    std::shared_ptr<Texture> importFromURL(int x, int y, int zoom);

private:
    TileTextureManager();
    ~TileTextureManager();

    static std::string getFilename(int x, int y, int zoom);
    static std::string getUrl(int x, int y, int zoom, const std::string &url);
};

#endif // TILETEXTUREMANAGER_H
