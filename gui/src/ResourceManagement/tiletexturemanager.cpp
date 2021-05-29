#include <ResourceManagement/tiletexturemanager.h>

#include <ResourceManagement/texturedownloader.h>

using namespace std;

TileTextureManager::TileTextureManager(): ResourceManager<Texture>() {}
TileTextureManager::~TileTextureManager() {}

void TileTextureManager::init(std::string base_url)
{
    m_baseUrl = base_url;
}


std::shared_ptr<Texture> TileTextureManager::importFromFile(string filename)
{
    if(get(filename) != nullptr)
        return get(filename);
    else {
        std::shared_ptr<Texture> t = std::make_shared<Texture>();
        t.get()->loadFromFile(filename);
	    add(filename, t);
	    return t;
    }
}


std::shared_ptr<Texture> TileTextureManager::importFromURL(int x, int y, int zoom)
{
    string filename = getFilename(x, y, zoom);
    // Hack to adapt raster tiles to image type
    for (auto ext: {".jpg", ".JPG", ".png", ".PNG"}) {
        auto pos = m_baseUrl.find(ext);
        if (pos != std::string::npos) {
            filename.replace(filename.end()-strlen(ext), filename.end(), ext);
        }
    }

    QString file_as_qstring = QFile::decodeName(filename.c_str());
    if(QFile::exists(file_as_qstring))
        return importFromFile(filename);

    if(!QDir("data").exists())
        QDir().mkdir("data");

    std::shared_ptr<Texture> t = std::make_shared<Texture>();
    QUrl url = QString(QObject::tr(getUrl(x, y, zoom, m_baseUrl).c_str()));
    TextureDownloader::getInstance()->download(url, file_as_qstring, t);
    add(filename, t);
    return t;
}


string TileTextureManager::getFilename(int x, int y, int zoom) {
    char filen[100];
    sprintf(filen, "data/%d-%d-%d.jpg", zoom, x, y);
    return string(filen);
}


string TileTextureManager::getUrl(int x, int y, int zoom, const std::string &url) {
    char curl[300];
    sprintf(curl, url.c_str(), zoom, x, y);
    return string(curl);
}
