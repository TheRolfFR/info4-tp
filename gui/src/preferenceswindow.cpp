#include "preferenceswindow.h"
#include <QFormLayout>
#include <QPushButton>

PreferencesWindow::PreferencesWindow(Config *c, QWidget *parent): QWidget(parent), cfg(c) {
    setWindowTitle(tr("Preferences"));
    QFormLayout *window_layout = new QFormLayout(this);
    proxy_enable = new QCheckBox;
    proxy_address = new QLineEdit(c->proxy_address);
    if (c->proxy_enabled)
        proxy_enable->setChecked(true);
    QPushButton *valid_btn = new QPushButton(tr("Accept"));
    window_layout->addRow(tr("Enable proxy"), proxy_enable);
    window_layout->addRow(tr("Proxy address"), proxy_address);
    window_layout->addRow(tr(""), valid_btn);
    connect(valid_btn, SIGNAL(clicked(bool)), this, SLOT(validated(bool)));
}

void PreferencesWindow::proxyToggled(int val) {
    if (val == Qt::Unchecked) {
        proxy_address->setDisabled(true);
    } else if (val == Qt::Checked) {
        proxy_address->setDisabled(false);
    }
}

void PreferencesWindow::validated(bool) {
    if (proxy_enable->isChecked()) {
        cfg->proxy_enabled = true;
        cfg->proxy_address = proxy_address->text();
    } else {
        cfg->proxy_enabled = false;
        cfg->proxy_address = proxy_address->text();
    }
    close();
}
