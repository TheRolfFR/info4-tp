#include <Data/vectortiledata.h>

#include <OpenGL/loadingmanager.h>
#include <geologic-core/objects/urban/roads.h>
#include <osmrouteloader.h>

#include <geologic-core/core/geologic-launcher/CoordinateSystemManager.h>

using std::cout;
using std::endl;

std::map<std::string, int> road_types = {
    {"motorway", 1},
    {"motorway_link", 1},
    {"trunk", 1},
    {"trunk_link", 1},
    {"primary", 2},
    {"primary_link", 2},
    {"secondary", 3},
    {"secondary_link", 3},
    {"tertiary", 3},
    {"tertiary_link", 3},
    {"unclassified", 3},
    {"residential", 4},
    {"service", 4},
    {"track", 4},
    {"default", 5}};

/**
 * \brief 	Default constructor of class VectorTileData
 *
 * \param 	None
 * \return 	None
 */
VectorTileData::VectorTileData(): UniqueData("VectorTileData")
{
    setStructureType(GL_LINES);
}

/**
 * \brief 	Default destructor of class VectorTileData
 *
 * \param 	None
 * \return 	None
 */
VectorTileData::~VectorTileData(){
	cout << "VectorTileData ~" << endl;
}


void VectorTileData::preloadThread() { 
    std::vector<float> vertices;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<std::vector<size_t>> lines;
    std::vector<int> types;

    std::unique_ptr<Roads> roads = std::make_unique<Roads>();
    CoordinateSystemManager* geoRefs = CoordinateSystemManager::getInstance();
    roads->setLoader(new OSMRouteLoader(geoRefs->getDataRef()));
	roads->load(m_filename.c_str());
    auto &edges = roads->getmEdge();
	size_t k = 0;
    for (auto &edge: edges) {
		size_t i = 0;
		std::vector<size_t> line;
        for(auto &point: edge.second->getNodes()) {
			x.push_back(point.getX());
			y.push_back(point.getY());
			if(i != 0) {
				line.push_back(k-1);
				types.push_back(road_types[edge.second->type]);
                //cout << "Type: " << road_types[edge.second->type] << endl;
				line.push_back(k);
				types.push_back(road_types[edge.second->type]);
			}
			i++;
			k++;
		}
		lines.push_back(line);
	}
	
	OGRCoordinateTransformation *t = OGRCreateCoordinateTransformation(geoRefs->getDataRef(), geoRefs->getViewRef());
	t->Transform(x.size(), &x[0], &y[0]);

	for(auto& line: lines) {
		for(auto& i: line) {
			vertices.push_back(x[i]); 
			vertices.push_back(y[i]); 
			vertices.push_back(0.0f); 
    	}
    }

    setVertices(vertices);
    setTypes(types);

    Data::preloadThread();
}


void VectorTileData::load()
{
    Data::load();

    if(m_types.size()) {
        // Destruction d'un éventuel ancien vboTypes
        if (glIsBuffer(m_vboTypes) == GL_TRUE)
            glDeleteBuffers(1, &m_vboTypes);

        // Génération de l'ID
        glGenBuffers(1, &m_vboTypes);
        // Verrouillage du vbo
        glBindBuffer(GL_ARRAY_BUFFER, m_vboTypes);

            // Allocation de la mémoire vidéo
            glBufferData(GL_ARRAY_BUFFER, m_types.size() * sizeof(int), &m_types[0], GL_STATIC_DRAW);

        // Déverrouillage de l'objet
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Verrouillage du VAO
        glBindVertexArray(m_vao);

            // Verrouillage du vbo
            glBindBuffer(GL_ARRAY_BUFFER, m_vboTypes);

                //Types
                glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 0, BUFFER_OFFSET(0));
                glEnableVertexAttribArray(3);
            
            // Deverrouillage du vbo
            glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Déverrouillage du VAO
        glBindVertexArray(m_vao);
    }
}
