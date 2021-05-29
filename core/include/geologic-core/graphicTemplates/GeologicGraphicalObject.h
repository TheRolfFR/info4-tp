/**
 * \file	GeologicGraphicalObject.h
 */

#ifndef GEOLOGICGRAPHICALOBJECT_H
#define GEOLOGICGRAPHICALOBJECT_H

#include <string>


class GeologicGraphicalObject {

    public:
        //*/ -------------------------------------------------
        GeologicGraphicalObject();
        virtual ~GeologicGraphicalObject();

        //*/ -------------------------------------------------
        std::string getType();

    protected:
        //*/ -------------------------------------------------
        virtual void setType() = 0;

        //*/ -------------------------------------------------
        std::string type;
};

#endif // GEOLOGICGRAPHICALOBJECT_H
