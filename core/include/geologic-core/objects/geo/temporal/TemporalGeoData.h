/**
 * \file	TemporalGeoData.h
 */

#ifndef TEMPORALGEODATA_H
#define TEMPORALGEODATA_H

#include "geologic-core/graphicTemplates/GeologicGraphicalObjectShape.h"
#include "geologic-core/graphicTemplates/GeologicCustomizeObject.h"
#include <string>
#include <time.h>


class TemporalGeoData : public GeologicGraphicalObjectShape, public GeologicCustomizeObject {

    public:
        //*/ -------------------------------------------------
        TemporalGeoData();
        virtual ~TemporalGeoData();

        //*/ -------------------------------------------------
        bool display(double timestamp);
        bool display(double timestampOrigin, double timestampDestination);

        //*/ -------------------------------------------------
        double timestamp;
};

#endif // TEMPORALGEODATA_H
