#include "Data/genericdata.h"
#include <iostream>

using namespace std;


GenericData::GenericData(string &n): GenericData(n.c_str())
{
}

GenericData::GenericData(const char *n): Data(n) {
}


GenericData::~GenericData() {
    //cout << "GenericData::~GenericData() (" << name << ")" << endl;
}


void GenericData::draw() {
    if(m_loaded) {
		if(m_indices.size()) {
            glDrawElements(m_structureType, m_indices.size(), GL_UNSIGNED_INT, 0);
		} else {
            glDrawArrays(m_structureType, 0, m_vertices.size()/3);
		}
    }
}
