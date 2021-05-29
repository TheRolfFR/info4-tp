#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include <map>


using namespace std;


template <class T>
class Library
{

    public:

        Library(): m__objects()
        {



        }

        ~Library()
        {



        }

        bool has(std::string path)
        {
            return m__objects.find(path) != m__objects.end();
        }

        void add(std::string path, T* object)
        {
            m__objects[path] = object;
                //m__objects.insert(pair<string, T*>(path, object));
        }

        T* get(std::string path)
        {
            if(has(path))
                return m__objects.at(path);
            else
                return nullptr;
        }

        void list()
        {
            for(auto it: m__objects)
                std::cout << "[Library]: " << it.first << std::endl;
        }

        void flush()
        {
            for(auto it: m__objects)
                delete(it.second);
            m__objects.clear();
        }

    private:

        std::map<std::string, T*> m__objects;

};

#endif

