#ifndef STATICDATA_H
#define STATICDATA_H

#include <Data/data.h>
#include <QtOpenGL/QtOpenGL>

/*!
 * \brief The StaticData class specializes Data to handle static data sets
 * (data which always displays the same data oever time)
 * Uses a display list to store the GL instructions
 * This class is pure virtual, and must be implemented by a child class.
 * \see Data
 */
class StaticData : public Data {
    GLuint list_index = 0;

protected:
    virtual void buildDisplayList() = 0;

public:
    StaticData(std::string &n): Data(n) {}
    StaticData(const char *n): Data(n) {}
    virtual ~StaticData() = 0;
//    virtual void draw() final;
//    virtual void draw(unsigned long long  simu_time) final;
};

#endif // STATICDATA_H
