#include <ResourceManagement/vectortiledatamanager.h>

#include <ResourceManagement/vectortiledatadownloader.h>
#include <Common/utils2.h>
#include <tagsbuilder.h>

#include <OpenGL/loadingmanager.h>

using namespace std;

VectorTileDataManager::VectorTileDataManager(): ResourceManager<VectorTileData>(),
    m_baseUrl()
{
}

VectorTileDataManager::~VectorTileDataManager() {}

void VectorTileDataManager::init(std::string base_url)
{
    m_baseUrl = base_url;
}


std::shared_ptr<VectorTileData> VectorTileDataManager::importFromFile(string filename)
{
    if(get(filename) != nullptr)
        return get(filename);
    else {
        std::shared_ptr<VectorTileData> t = std::make_shared<VectorTileData>();
        std::shared_ptr<VectorTileData> tt = t;
        tt->setFilename(filename);
		std::shared_ptr<Data> td = std::dynamic_pointer_cast<Data>(move(tt));
        LoadingManager::getInstance()->load(td);
	    add(filename, t);
	    return t;
    }
}


std::shared_ptr<VectorTileData> VectorTileDataManager::importFromURL(int x, int y, int zoom)
{
    string filename = getFilename(x, y, zoom);
    if(get(filename) != nullptr)
        return get(filename);

    QString file_as_qstring = QFile::decodeName(filename.c_str());
    if(QFile::exists(file_as_qstring)) {
        return importFromFile(filename);
    }

	if(!QDir("data").exists())
		QDir().mkdir("data");

	std::shared_ptr<VectorTileData> t = std::make_shared<VectorTileData>();
	QUrl url = QString(QObject::tr(getUrl(x, y, zoom, m_baseUrl).c_str()));
	VectorTileDataDownloader::getInstance()->download(url, file_as_qstring, t);
	add(filename, t);
	return t;
}


string VectorTileDataManager::getFilename(int x, int y, int zoom) {
    char filen[100];
    sprintf(filen, "data/%d-%d-%d.osm", zoom, x, y);
    return string(filen);
}


string VectorTileDataManager::getUrl(int x, int y, int zoom, const std::string &url) {
    double bbox[4];    
    bbox[1] = Utils::utm2lon(Utils::tile2utm(x, zoom));
    bbox[0] = Utils::utm2lat(Utils::tile2utm(y + 1, zoom));
    bbox[3] = Utils::utm2lon(Utils::tile2utm(x + 1, zoom));
    bbox[2] = Utils::utm2lat(Utils::tile2utm(y, zoom));
    TagsBuilder tb(url);
    tb.setBoudingBox(bbox);
    tb.setoutputformat("xml");

    std::string first_class = "motorway|motorway_link|trunk|trunk_link";
    std::string second_class = "primary|primary_link|secondary|secondary_link";
    std::string third_class = "tertiary|tertiary_link|unclassified";
    std::string fourth_class = "residential|living_street|track|service";


    // https://wiki.openstreetmap.org/wiki/Key:highway
	if(zoom < 9) {
        tb.tag("highway", "~", first_class);
	} else if( zoom < 10) {
        tb.tag("highway", "~", first_class + "|" + second_class);
	} else if( zoom < 13) {
        tb.tag("highway", "~", first_class + "|" + second_class + "|" + third_class);
    } else {
        tb.tag("highway", "~", first_class + "|" + second_class + "|" + third_class + "|" + fourth_class);
    }
    return tb.toString();
}
