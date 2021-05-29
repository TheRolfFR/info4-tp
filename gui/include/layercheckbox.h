#pragma once

#include <QCheckBox>
#include <Scene/layer.h>

class LayerCheckBox: public QCheckBox {
    Q_OBJECT

public:
    LayerCheckBox() = delete;
    LayerCheckBox(Layer* l, const QString &label, QWidget *parent);
    ~LayerCheckBox() {}


    Layer *managed_layer;

public slots:
    void setState(int state);
};
