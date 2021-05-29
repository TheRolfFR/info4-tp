/**
 * \file	GeologicGraphicalObjectShape.h
 */

#ifndef GEOLOGICGRAPHICALOBJECTSHAPE_H
#define GEOLOGICGRAPHICALOBJECTSHAPE_H

#include "geologic-core/graphicTemplates/GeologicGraphicalObject.h"
#include <time.h>


class GeologicGraphicalObjectShape : public GeologicGraphicalObject {

    public:
        //*/ -------------------------------------------------
        GeologicGraphicalObjectShape();
        virtual ~GeologicGraphicalObjectShape();

        //*/ -------------------------------------------------
        virtual bool display(double timestamp) = 0;
        virtual bool display(double timestampOrigin, double timestampDestination) = 0;
        void setType();
};

#endif // GEOLOGICGRAPHICALOBJECTSHAPE_H
