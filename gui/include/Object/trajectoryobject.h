/**
 * \file	TRAJECTORYOBJECT.h
 */

#ifndef TRAJECTORYOBJECT_h
#define TRAJECTORYOBJECT_h


#include <Object/object.h>
#include <geologic-core/objects/dynamic/Trajectory.h>


class TrajectoryObject : public Object {

    public:
        //*/ -------------------------------------------------
        TrajectoryObject(Trajectory* trajectory);
        virtual ~TrajectoryObject();

        //*/ -------------------------------------------------
        Trajectory* trajectory;
};


#endif // TRAJECTORYOBJECT_h 
