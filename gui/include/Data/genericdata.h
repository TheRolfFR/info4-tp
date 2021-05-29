#pragma once

#include <Data/data.h>

class GenericData: public Data {
public:
    GenericData(std::string &n);
    GenericData(const char *n);
    virtual ~GenericData();

    virtual void draw();
};
