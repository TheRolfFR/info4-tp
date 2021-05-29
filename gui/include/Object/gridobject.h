#pragma once

#include <Object/childobject.h>
#include <geologic-core/objects/geo/untemporal/Grid.h>


class GridObject : public ChildObject {

    public:
        //*/ -------------------------------------------------
        GridObject(View* view, std::shared_ptr<Shader> shader, Grid* grid);
        virtual ~GridObject();

        //*/ -------------------------------------------------
        Grid* grid;
};
