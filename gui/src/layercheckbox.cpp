#include "layercheckbox.h"
#include <iostream>
#include <QMouseEvent>

using namespace std;

/*!
 * \brief LayerCheckBox::LayerCheckBox constructor
 * \param o the object managed by the checkbox
 * \param label the label displayed besides the checkbox
 * \param parent the parent widget
 * Initial states is checked and the checkbox stateChanged signal is connected to its slot.
 */
LayerCheckBox::LayerCheckBox(Layer* l, const QString &label, QWidget *parent): QCheckBox{label, parent}, managed_layer(l) {
    setChecked(true);
    connect(this, SIGNAL(stateChanged(int)), this, SLOT(setState(int)));
    //connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(rightClick(QPoint)));
}

void LayerCheckBox::setState(int state) {
    if (state == Qt::Unchecked) {
        managed_layer->setHidden();
    } else if (state == Qt::Checked) {
        managed_layer->setVisible();
    }
}


