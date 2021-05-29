#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <ResourceManagement/resourcemanager.hpp>
#include <Data/data.h>

class DataManager: public ResourceManager<Data> {

public:
    static DataManager* getInstance(){
        static DataManager* s_instance = new DataManager();
        return s_instance;
    }

    virtual void init();
    virtual void load();

private:
    DataManager();
    virtual ~DataManager();

};

#endif // DATAMANAGER_H
