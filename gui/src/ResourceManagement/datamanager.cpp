#include <ResourceManagement/datamanager.h>

#include <OpenGL/loadingmanager.h>

#include <Data/rastertiledata.h>
#include <Data/pointdata.h>
#include <Data/quaddata.h>
#include <Data/linedata.h>

using namespace std;

DataManager::DataManager(): ResourceManager<Data>() {}
DataManager::~DataManager() {}

void DataManager::init()
{
	std::shared_ptr<Data> point = std::make_shared<PointData>();
    add("point", point);
	std::shared_ptr<Data> quad = std::make_shared<QuadData>();
    add("quad", quad);
	std::shared_ptr<Data> line = std::make_shared<LineData>();
    add("line", line);
}


void DataManager::load()
{
	std::shared_ptr<Data> point = get("point");
    LoadingManager::getInstance()->load(point);
	std::shared_ptr<Data> quad = get("quad");
    LoadingManager::getInstance()->load(quad);
	std::shared_ptr<Data> line = get("line");
    LoadingManager::getInstance()->load(line);
}
