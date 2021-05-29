#pragma once

#include <vector>

#include <Data/data.h>

class LoadingManager {
private:
    std::vector<std::shared_ptr<Data>> m_datas;
    QMutex m_mutex;
public:
    static LoadingManager* getInstance(){
        static LoadingManager* s_instance = new LoadingManager();
        return s_instance;
    }

    void load(std::shared_ptr<Data> data);
    void update();

private:
    LoadingManager();
    ~LoadingManager();

};
