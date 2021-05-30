#include "mygeologicbaseclass.h"

#include "boundariesobject.h"

MyGeologicBaseClass::MyGeologicBaseClass() : SceneManager()
{

}

void MyGeologicBaseClass::init() {
        SceneManager::init();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        getMainView()->addLayer("zone"); // Adding a new layer named 'zone' which links to shaders zone; TODO: create own shader!

        BoundariesObject *my_object = new BoundariesObject(getMainView());
        getMainView()->addObject(my_object);

        getController()->bindWheel(1, [this]() {
            getMainView()->zoomIn();
            needsViewUpdate();
        });

        getController()->bindWheel(-1, [this]() {
            getMainView()->zoomOut();
            needsViewUpdate();
        });

        getController()->bindDrag(Qt::LeftButton, [this](QVector2D, QVector2D, QVector2D offset) {
            getMainView()->moveViewCenter((int)offset.x(), -(int)offset.y());
            needsViewUpdate();
        });

        getController()->bindMove([this](QVector2D pos, QVector2D) {
            double x = getMainView()->getViewXMin() + ((getMainView()->getViewXMax() - getMainView()->getViewXMin()) * pos.x() / getMainView()->getScreenWidth());
            double y = getMainView()->getViewYMin() + ((getMainView()->getViewYMax() - getMainView()->getViewYMin()) * (getMainView()->getScreenHeight() - pos.y()) / getMainView()->getScreenHeight());
            updateLabel(QVector2D(x, y));
        });
}

void MyGeologicBaseClass::draw() {

}
