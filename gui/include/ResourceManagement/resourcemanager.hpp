#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <memory>
#include <iostream>

template <typename T>
class ResourceManager {
protected:
    std::map<std::string, std::shared_ptr<T>> m_library;

public:
    static ResourceManager<T>* getInstance() noexcept(std::is_nothrow_constructible<T>::value) {
        // Guaranteed to be destroyed.
        // Instantiated on first use.
        // Thread safe in C++11
        static ResourceManager<T>* s_instance;
        return s_instance;
    }

    virtual void init() {};
    virtual void load() {};

    virtual void flush() {};

    void add(std::string& key, std::shared_ptr<T>& value){
        m_library[key] = value;
    }

    void add(const char* key, std::shared_ptr<T>& value){
        m_library[std::string(key)] = value;
    }

    std::shared_ptr<T> get(std::string& key)
    {
        return m_library[key];
    }

    std::shared_ptr<T> get(const char* key)
    {
        return m_library[std::string(key)];
    }

protected:
    ResourceManager() noexcept = default;
    virtual ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

};

#endif // RESOURCEMANAGER_H
