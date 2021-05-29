#include <Data/staticdata.h>

StaticData::~StaticData() {}
/*
void StaticData::draw() {
    if (list_index == 0) {
        list_index = glGenLists(1);
        if (list_index == 0)
            return;
        glNewList(list_index, GL_COMPILE);
        buildDisplayList();
        glEndList();
    }
    if (list_index != 0) {
        glCallList(list_index);
    }
}

void StaticData::draw(unsigned long long simu_time) {
    draw();
}*/
