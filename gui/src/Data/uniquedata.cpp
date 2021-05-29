#include "Data/uniquedata.h"
#include <geologic-core/utils/customToolbox.h>
#include <iostream>

#include <ResourceManagement/shadermanager.h>

using namespace std;


UniqueData::UniqueData(string &n): 
    UniqueData(n.c_str())
{
}


UniqueData::UniqueData(const char* n): 
    Data(n)
{
}


UniqueData::~UniqueData() {
    //cout << "UniqueData::~UniqueData() (" << name << ")" << endl;
}


void UniqueData::draw() {
    if(m_loaded) {
        bind();
		if(m_indices.size()) {
            glDrawElements(m_structureType, m_indices.size(), GL_UNSIGNED_INT, 0);
		} else {
            glDrawArrays(m_structureType, 0, m_vertices.size()/3);
		}
        glBindVertexArray(0);
    }
}
