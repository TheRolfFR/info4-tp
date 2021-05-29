#include <ResourceManagement/texturemanager.h>

using namespace std;

TextureManager::TextureManager(): ResourceManager<Texture>() {}
TextureManager::~TextureManager() {}

void TextureManager::init()
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    add("Textures/loading.png", texture);
}


void TextureManager::load()
{
    get("Textures/loading.png")->loadFromFile("Textures/loading.png");
}


std::shared_ptr<Texture> TextureManager::importFromFile(string filename)
{
    if(get(filename) != nullptr)
        return get(filename);
    else {
	    std::shared_ptr<Texture> t = std::make_shared<Texture>();
        t->loadFromFile(filename);
	    add(filename, t);
	    return t;
    }
}
