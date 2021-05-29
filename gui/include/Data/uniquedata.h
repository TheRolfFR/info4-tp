#pragma once

#include <Data/data.h>

class UniqueData: public Data {
public:
    UniqueData(std::string &n);
    UniqueData(const char* n);
    virtual ~UniqueData();

    virtual void draw();
};
