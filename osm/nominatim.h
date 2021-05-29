#ifndef NOMINATIM_H
#define NOMINATIM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <OpenGL/gldisplay.h>

class NominatimResult: public QListWidgetItem {
    double _longitude;
    double _latitude;

public:
    explicit NominatimResult(QListWidget *parent = 0, const QString &text = "No result to display", double lon = 0.0, double lat = 0.0);
    double getLongitude() const {return _longitude;}
    double getLatitude() const {return _latitude;}
    ~NominatimResult() {}
};

class NominatimPanel: public QWidget {
    Q_OBJECT

    QNetworkAccessManager *_qnam;
    QLineEdit *_query_text;
    QPushButton *_search_btn;
    QListWidget *_results;
    QPushButton *_go_btn;
    GLDisplay *_gl_display;
    QNetworkReply *_reply = nullptr;

public:
    NominatimPanel(QWidget *parent, GLDisplay *gld, QNetworkAccessManager *qnam = nullptr);
    ~NominatimPanel() {delete _qnam;}

public slots:
    void search_clicked();
    void go_clicked();
    void result_received();
};

#endif // NOMINATIM_H
