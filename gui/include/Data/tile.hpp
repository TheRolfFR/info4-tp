#ifndef TILE_HPP
#define TILE_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <ogr_spatialref.h>
#include <ogr_geometry.h>
#include <string>
#include <iostream>

using namespace std;

/*!
 * \function init function is used to init various tile parameters (coordinates reprojections, etc.)
 * \param content the tile content itself (implemented by tile content providers such as OpenStreetMap)
 * \param x the tile x index (from left to right)
 * \param y the tile y index (from top to bottom)
 * \param zoom the zoom level (earth has 2^zoom * 2^zoom tiles for given zoom value)
 */
template <typename T>
void init(T content, int x, int y, int z) {
}

/*!
 * \function load loads tile content from file named filename to function parameter content
 * \param content the tile content itself (implemented by tile content providers such as OpenStreetMap)
 * \param filename the path to the resource file
 */
template <typename T>
void load(T content, std::string filename) {
}

/*!
 * \function convert converts tile content from spatial reference from to spatial reference to
 * \param content the tile content itself (implemented by tile content providers such as OpenStreetMap)
 * \param from content source spatial reference, must not be null
 * \param to target spatial reference, must not be null
 */
template <typename T>
void convert(T &content, OGRSpatialReference *&from, OGRSpatialReference *&to) {
}

/*!
 * \function draw draws the tile content in the GLDisplay
 * \param content the tile content itself (implemented by tile content providers such as OpenStreetMap)
 */
template <typename T>
void draw(T content) {
}

/*!
 * \function clear frees memory and resources used by tile content
 * \param content the tile content itself (implemented by tile content providers such as OpenStreetMap)
 */
template <typename T>
void clear(T content) {
}

/*!
 * \function getFilename return the tile resource file for a given tile
 * \param content the tile content itself (implemented by tile content providers such as OpenStreetMap)
 * \param x the tile x index (from left to right)
 * \param y the tile y index (from top to bottom)
 * \param zoom the zoom level (earth has 2^zoom * 2^zoom tiles for given zoom value)
 */
template <typename T>
std::string getFilename(T content, int x, int y, int z) {
    return std::string("");
}

/*!
 * \function getUrl returns the target URL for a given tile (used to query tile to a remote service)
 * \param content the tile content itself (implemented by tile content providers such as OpenStreetMap)
 * \param x the tile x index (from left to right)
 * \param y the tile y index (from top to bottom)
 * \param zoom the zoom level (from 1 to 18)
 * \param url the URL template (in the printf format type)
 */
template <typename T>
std::string getUrl(T content, int x, int y, int z, const std::string &url) {
    return std::string("");
}

template <typename T>
class Tile {

    bool _loading = false;              ///< Boolean value specifying whether the file is loading
    bool _ready = false;                ///< Boolean value specifying whether the data is ready to render
    bool _converting = false;           ///< Boolean value specifying whether the data is loaded and being converted (from data to view spatial reference)
    QNetworkAccessManager *_qnam;       ///< Qt network access manager provided by the tile owner
    OGRSpatialReference *_dataref;      ///< Spatial reference in which the data is stored
    OGRSpatialReference *_viewref;      ///< Spatial reference in which the data is displayed (projection)
    std::string _filename;              ///< name of the file where the data is stored
    T _content;                         ///< the actual content of the tile
    QFuture<void> _thread_result;       ///< Result of the threaded coordinates conversion
    std::string _base_url;              ///< Base URL to be passed to content

public:
    Tile(int zoom, int x, int y, OGRSpatialReference *d, OGRSpatialReference *v, QNetworkAccessManager *net, const std::string &url);
    ~Tile() {}
    void display();
    void clean();
    void convert_thread_wrapper();
    void load_thread_wrapper();

    int _zoom;
    int _x;
    int _y;

};

template <typename T>
Tile<T>::Tile(int zoom, int x, int y, OGRSpatialReference *d, OGRSpatialReference *v, QNetworkAccessManager *net, const std::__cxx11::string &url_):
    _qnam(net), _dataref(d), _viewref(v), _base_url(url_), _zoom(zoom), _x(x), _y(y) {
//    std::cout << "Tile<T>::Tile " << url_ << std::endl;
    _filename = getFilename(_content, x, y, zoom);
    // Hack to adapt raster tiles to image type
    for (auto ext: {".jpg", ".JPG", ".png", ".PNG"}) {
        auto pos = _base_url.find(ext);
        if (pos != std::string::npos) {
            _filename.replace(_filename.end()-strlen(ext), _filename.end(), ext);
        }
    }
    init(_content, x, y, zoom);

    QString file_as_qstring = QFile::decodeName(_filename.c_str());
    if(QFile::exists(file_as_qstring)) {
        _qobj._downloaded = true;
    } else if (_qnam != nullptr) {
        //std::cout << "Tile<T>::Tile " << getUrl(_content, x, y, zoom, _base_url) << std::endl;
        QUrl url(QObject::tr(getUrl(_content, x, y, zoom, _base_url).c_str()));
        //std::cout << "Tile<T>::Tile " << url.toString().toStdString() << std::endl;
        QNetworkRequest request(url);
        request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64…) Gecko/20100101 Firefox/61.0");
        _qobj._reply = _qnam->get(request);
        _qobj.setFilename(_filename);
        _qobj.connect(_qobj._reply, SIGNAL(finished()), &_qobj, SLOT(replyFinished()));
    }
    //std::cout << "Tile<T>::Tile: ok" << std::endl;
}


void DummyQObject::replyFinished() {
    QString filen(_filename.c_str());
    qint64 size = _reply->bytesAvailable(), bytes_read;
    char *buffer = new char[size];
    bytes_read = _reply->read(buffer, size);
    QFile f(filen);
    if (size != 0 && bytes_read == size && _reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200
            && f.open(QIODevice::WriteOnly)) {
        f.write(buffer, size);
        f.close();
        _downloaded = true;
    }
    _reply->deleteLater();
}

template <typename T>
void Tile<T>::convert_thread_wrapper() {
    convert(_content, _dataref, _viewref);
}

template <typename T>
void Tile<T>::load_thread_wrapper() {
    load(_content, _filename);
}

template <typename T>
void Tile<T>::display() {

    if (_dataref == nullptr || _viewref == nullptr)
        return;

    if (_qobj._downloaded == true && _loading == false && _converting == false && _ready == false) {
        // Load file data
        //std::cout << "Load tile " << _zoom << "-" << _x << "-" << _y << std::endl;
        _thread_result = QtConcurrent::run(this, &Tile<T>::load_thread_wrapper);
        _loading = true;
    } else if (_qobj._downloaded == true && _loading == true && _converting == false && _ready == false) {
        // Convert from data spatial reference to view spatial reference (threaded)
        if (_thread_result.isFinished()) {
            //std::cout << "Loaded tile " << _zoom << "-" << _x << "-" << _y << std::endl;
            _thread_result = QtConcurrent::run(this, &Tile<T>::convert_thread_wrapper);
            //std::cout << "Converting tile " << _zoom << "-" << _x << "-" << _y << std::endl;
            _converting = true;
        }
    } else if (_qobj._downloaded == true && _loading == true && _converting == true && _ready == false) {
        // Check if data is converted
        if (_thread_result.isFinished()) {
            _ready = true;
            //std::cout << "Converted tile " << _zoom << "-" << _x << "-" << _y << std::endl;
        }
    } else if (_qobj._downloaded == true && _loading == true && _converting == true && _ready == true) {
        // Display data
        draw(_content);
    }
}

template <typename T>
void Tile<T>::clean() {
    clear(_content);
}

#endif // TILE_HPP
