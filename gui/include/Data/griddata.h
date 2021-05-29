/**
 * \file	GRIDDATA.h
 */

#ifndef GRIDDATA_h
#define GRIDDATA_h


#include <Data/data.h>
#include <geologic-core/objects/geo/untemporal/Grid.h>
#include <Data/meshdata.h>


class GridData : public Data {

    public:
        //*/ -------------------------------------------------
        GridData();
        virtual ~GridData();
};


#endif // GRIDDATA_h 
