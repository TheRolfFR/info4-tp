#include "Data/data.h"
#include <geologic-core/utils/customToolbox.h>
#include <iostream>

#include <ResourceManagement/shadermanager.h>

using namespace std;


Data::Data(string &n): 
    Data(n.c_str())
{
}

Data::Data(const char *n): 
    QThread(),
    m_name(n),
    m_eboIndices(),
    m_vboVertices(),
    m_vboUVs(),
    m_vao(),
    m_vertices(),
    m_indices(),
    m_uvs(),
    m_structureType(GL_TRIANGLES),
    m_preloaded(false),
    m_loaded(false),
    m_generic(true)
{
}


Data::~Data() {
    //cout << "Data::~Data() (" << name << ")" << endl;
}

void Data::load() {
    preloadThread();

    // Destruction d'un éventuel ancien vboVertices
	if (glIsBuffer(m_vboVertices) == GL_TRUE)
		glDeleteBuffers(1, &m_vboVertices);

	// Génération de l'ID
	glGenBuffers(1, &m_vboVertices);
	// Verrouillage du vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);

		// Allocation de la mémoire vidéo
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);

	// Déverrouillage de l'objet
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    if(m_uvs.size() > 0) {
        // Destruction d'un éventuel ancien VBO
        if (glIsBuffer(m_vboUVs) == GL_TRUE)
            glDeleteBuffers(1, &m_vboUVs);

        // Génération de l'ID
        glGenBuffers(1, &m_vboUVs);
        // Verrouillage du VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_vboUVs);

            // Allocation de la mémoire vidéo
            glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(float), &m_uvs[0], GL_STATIC_DRAW);

        // Déverrouillage de l'objet
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
	
	// Destruction d'un éventuel ancien VAO
	if (glIsVertexArray(m_vao) == GL_TRUE)
		glDeleteVertexArrays(1, &m_vao);

	// Génération de l'identifiant du VAO
	glGenVertexArrays(1, &m_vao);
	// Verrouillage du VAO
	glBindVertexArray(m_vao);

		// Verrouillage du vbo
		glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);

			//Vertices
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);
		
        // Deverrouillage du vbo
		glBindBuffer(GL_ARRAY_BUFFER, 0);
			
        if(m_uvs.size() > 0) {
            // Verrouillage du vbo
            glBindBuffer(GL_ARRAY_BUFFER, m_vboUVs);
                //UVs
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                glEnableVertexAttribArray(1);
            // Deverrouillage du vbo
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

		// Destruction d'un éventuel ancien EBO
		if (glIsBuffer(m_eboIndices) == GL_TRUE)
			glDeleteBuffers(1, &m_eboIndices);
		
		if(m_indices.size()) {
			// Génération de l'ID
			glGenBuffers(1, &m_eboIndices);
			// Verrouillage du EBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboIndices);

				// Allocation de la mémoire vidéo
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

            // Ne pas déverouiller l'EBO ! Il doit rester associé au VAO
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	// Déverrouillage du VAO
	glBindVertexArray(0);

    m_loaded = true;
}

void Data::bind() {
    glBindVertexArray(m_vao);
}
