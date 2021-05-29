#include <ResourceManagement/vectortiledatadownloader.h>
#include <iostream>

#include <QFile>

#include <geologic-core/objects/urban/roads.h>
#include <osmrouteloader.h>

#include <OpenGL/loadingmanager.h>

using namespace std;

VectorTileDataDownloader* VectorTileDataDownloader::s_instance;
QMutex VectorTileDataDownloader::s_createMutex;

DataDownloadTask::DataDownloadTask(QUrl url, QString filename, std::shared_ptr<VectorTileData>& t): QObject(),
    m_url(url),
    m_filename(filename),
    m_data(t),
    m_reply()
{
}

void DataDownloadTask::start(QNetworkAccessManager* manager)
{
    QNetworkRequest request(m_url);
    request.setRawHeader("User-Agent", "MobilityVanet");
    m_reply = manager->get(request);
}

VectorTileDataDownloader::VectorTileDataDownloader() : m_manager(),
    m_pending(),
    m_active()
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedEvent(QNetworkReply*)));
}


VectorTileDataDownloader::~VectorTileDataDownloader() {
}


void VectorTileDataDownloader::update() {
    m_takeMutex.lock();
        if(m_pending.size() > 0 && m_active.size() < 1) {    
            DataDownloadTask* dt = m_pending.front();
            if(m_active.find(dt->getUrl()) == m_active.end()) {
                m_active.insert(pair<QUrl, DataDownloadTask*>(dt->getUrl(), dt));
                dt->start(m_manager);
            } else {
                delete(dt);
            }
            m_pending.pop();
        }
    m_takeMutex.unlock();
}


VectorTileDataDownloader* VectorTileDataDownloader::getInstance() {
    s_createMutex.lock();
        if(s_instance == nullptr)
        {
            s_instance = new VectorTileDataDownloader();
        }
    s_createMutex.unlock();
    return s_instance;
}


void VectorTileDataDownloader::download(QUrl url, QString destination, std::shared_ptr<VectorTileData> t) {
    DataDownloadTask* dt = new DataDownloadTask(url, destination, t); 
    m_pending.push(dt);
}


void VectorTileDataDownloader::flushPending() {
    m_takeMutex.lock();
        while(!m_pending.empty())
            m_pending.pop();
    m_takeMutex.unlock();
}


void VectorTileDataDownloader::finishedEvent(QNetworkReply* reply) {
    DataDownloadTask* dt = m_active[reply->url()];

    qint64 size = reply->bytesAvailable();
    char *buffer = new char[size];

    qint64 bytes_read = reply->read(buffer, size);

    QFile f(dt->getFilename());
    int err = f.open(QIODevice::WriteOnly);
    if (size != 0 && bytes_read == size && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200 && err) {
        f.write(buffer, size);
        f.close();
        
        std::shared_ptr<VectorTileData> vdata = move(dt->getData());
        vdata->setFilename(dt->getFilename().toStdString());
        std::shared_ptr<Data> data = move(std::dynamic_pointer_cast<Data>(vdata));
        LoadingManager::getInstance()->load(data);
        qInfo() << "Cached: " << dt->getFilename();
    } else {
        qInfo() << "ERROR: " << dt->getUrl() << " : " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qInfo() << "ERROR:     " << size << " : " << bytes_read << " : " << err; 
    }

    delete(dt);
    
    reply->deleteLater();
    
    m_takeMutex.lock();
        m_active.erase(m_active.find(reply->url()));
    m_takeMutex.unlock();
}
