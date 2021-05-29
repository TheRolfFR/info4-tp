#include <ResourceManagement/shadermanager.h>

using namespace std;

ShaderManager::ShaderManager(): ResourceManager<Shader>() {}
ShaderManager::~ShaderManager() {}

void ShaderManager::init()
{
	std::shared_ptr<Shader> background_shader = std::make_shared<Shader>("background");
    add("background", background_shader);
}


void ShaderManager::load()
{
    get("background")->load();
}
