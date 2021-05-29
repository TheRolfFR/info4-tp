#include "nominatim.h"
#include <QVBoxLayout>
#include <ogr_geometry.h>
#include <QNetworkProxy>
#include <QNetworkRequest>
#include <QUrl>
#include <QXmlStreamReader>
#include <QXmlInputSource>
#include <QXmlStreamAttribute>

NominatimPanel::NominatimPanel(QWidget *parent, GLDisplay *gld, QNetworkAccessManager *qnam): QWidget(parent), _qnam(qnam), _gl_display(gld) {
    setWindowTitle("Nominatim"); // Useless?
    setLayout(new QVBoxLayout(this));
    QVBoxLayout *my_layout = reinterpret_cast<QVBoxLayout *>(layout());
    // Build GUI elements: 1) search box
    _query_text = new QLineEdit(this);
    _query_text->setPlaceholderText(tr("Enter your query here"));
    // 2) Search button
    _search_btn = new QPushButton(tr("Search"), this);
    // 3) Query result
    _results = new QListWidget(this);
    _results->setMaximumHeight(250);
    _results->setMinimumHeight(250);
    // 4) Go button
    _go_btn = new QPushButton(tr("Go to location"), this);

    // Add widgets to layout
    my_layout->addWidget(_query_text);
    my_layout->addWidget(_search_btn);
    my_layout->addWidget(_results);
    my_layout->addWidget(_go_btn);
    my_layout->addStretch();

    // Connect events
    connect(_query_text, SIGNAL(returnPressed()), this, SLOT(search_clicked()));
    connect(_search_btn, SIGNAL(clicked()), this, SLOT(search_clicked()));
    connect(_go_btn, SIGNAL(clicked()), this, SLOT(go_clicked()));

    // Initialize network access
    _qnam = new QNetworkAccessManager;
    _qnam->setProxy(QNetworkProxy(QNetworkProxy::DefaultProxy));
}

void NominatimPanel::search_clicked() {
    QString query_string = "https://nominatim.openstreetmap.org/search?q=" + _query_text->text().replace(" ", "+") + "&format=xml&polygon=0&addressdetails=0";
    _reply = _qnam->get(QNetworkRequest(QUrl(query_string)));
    connect(_reply, SIGNAL(finished()), this, SLOT(result_received()));
}

void NominatimPanel::go_clicked() {
    NominatimResult *choice = reinterpret_cast<NominatimResult *>(_results->currentItem());
    OGRPoint p{choice->getLongitude(), choice->getLatitude()};
//    _gl_display->getMainView()->setCenter(p);
}

void NominatimPanel::result_received() {
    if (_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) != 200)
        return;
    _results->clear();
    QXmlStreamReader reader(_reply->readAll());
    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType tok = reader.readNext();
        if (tok == QXmlStreamReader::StartElement) {
            if (reader.name().toString() == "place") {
                new NominatimResult(_results, reader.attributes().value("display_name").toString(),
                                    reader.attributes().value("lon").toDouble(), reader.attributes().value("lat").toDouble());
            }
        }
    }
    _reply->deleteLater();
}

NominatimResult::NominatimResult(QListWidget *parent, const QString &text,double lon,
                                 double lat): QListWidgetItem (text, parent), _longitude(lon), _latitude(lat) {
}
