#ifndef VECTORTILEDATAMANAGER_H
#define VECTORTILEDATAMANAGER_H

#include <ResourceManagement/resourcemanager.hpp>
#include <Data/vectortiledata.h>

class VectorTileDataManager: public ResourceManager<VectorTileData> {
    // needs to be friend in order to 
    // access the private constructor/destructor
    friend class ResourceManager<VectorTileData>; 
private:
    std::string m_baseUrl;

public:
    static VectorTileDataManager* getInstance(){
        static VectorTileDataManager* s_instance = new VectorTileDataManager();
        return s_instance;
    }

    virtual void flush() override{
        m_library.clear();
    }

    void init(std::string baseUrl);
    void load(std::string baseUrl);

    std::shared_ptr<VectorTileData> importFromFile(std::string id);
    std::shared_ptr<VectorTileData> importFromURL(int x, int y, int zoom);

    int size() {return m_library.size(); };

private:
    VectorTileDataManager();
    ~VectorTileDataManager();

    static std::string getFilename(int x, int y, int zoom);
    static std::string getUrl(int x, int y, int zoom, const std::string &url);
};

#endif // VECTORTILEDATAMANAGER_H
