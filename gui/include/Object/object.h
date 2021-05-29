#pragma once

#include <string>
#include <vector>

#include <Material/material.h>
#include <Data/data.h>

class Object {
protected:
    std::string m_name;
    QMatrix4x4 m_model;
    QMatrix4x4 m_proxy_model;
    
    bool m_hidden;

public:
    Object(std::string &name);
    Object(const char* name);
    virtual ~Object();
    
    virtual void update(QMatrix4x4& model, double t);

    std::string getName() { return m_name; };
    void setName(std::string s) { m_name = s; };

    virtual void setHidden(bool h) { m_hidden = h; };
    virtual void setHidden() { m_hidden = true; };
    virtual void setVisible() { m_hidden = false; };
    virtual void toggleVisibility() { m_hidden = !m_hidden; };
};
