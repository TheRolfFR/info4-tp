#ifndef PREFERENCESWINDOW_H
#define PREFERENCESWINDOW_H

#include <QCheckBox>
#include <QLineEdit>
#include <QWidget>
#include <Common/config.h>

class PreferencesWindow: public QWidget {
    Q_OBJECT

    QCheckBox *proxy_enable;
    QLineEdit *proxy_address;
    Config *cfg;

public:
    PreferencesWindow(Config *c, QWidget *parent = nullptr);

public slots:
    void proxyToggled(int val);
    void validated(bool);
};

#endif // PREFERENCESWINDOW_H
