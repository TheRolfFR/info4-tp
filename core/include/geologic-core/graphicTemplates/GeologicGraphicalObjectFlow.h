/**
 * \file	GeologicGraphicalObjectFlow.h
 */


#ifndef GEOLOGICGRAPHICALOBJECTFLOW_H
#define GEOLOGICGRAPHICALOBJECTFLOW_H

#include "geologic-core/graphicTemplates/GeologicGraphicalObject.h"
#include <time.h>


class GeologicGraphicalObjectFlow : public GeologicGraphicalObject {

    public:
        //*/ -------------------------------------------------
        GeologicGraphicalObjectFlow();
        virtual ~GeologicGraphicalObjectFlow();

        //*/ -------------------------------------------------
        virtual double display(time_t timestamp) = 0;
        void setType();

};

#endif // GEOLOGICGRAPHICALOBJECTFLOW_H
