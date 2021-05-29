#include <ResourceManagement/texturedownloader.h>
#include <iostream>

#include <QFile>

using namespace std;

TextureDownloader* TextureDownloader::s_instance;
QMutex TextureDownloader::s_createMutex;

DownloadTask::DownloadTask(QUrl url, QString filename, std::shared_ptr<Texture> t): QObject(),
    m_url(url),
    m_filename(filename),
    m_texture(t),
    m_reply()
{
}

void DownloadTask::start(QNetworkAccessManager* manager)
{
    QNetworkRequest request(m_url);
    request.setRawHeader("User-Agent", "MobilityVanet");
    m_reply = manager->get(request);
}

TextureDownloader::TextureDownloader() : m_manager(),
    m_pending(),
    m_active()
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedEvent(QNetworkReply*)));
}


TextureDownloader::~TextureDownloader() {
    if (m_manager)
        delete m_manager;
}


void TextureDownloader::update() {
    m_takeMutex.lock();
        if(m_pending.size() > 0 && m_active.size() < 2) {    
            DownloadTask* dt = m_pending.front();
            if(m_active.find(dt->getUrl()) == m_active.end()) {
                m_active.insert(pair<QUrl, DownloadTask*>(dt->getUrl(), dt));
                dt->start(m_manager);
            } else {
                delete(dt);
            }
            m_pending.pop();
        }
    m_takeMutex.unlock();
}


TextureDownloader* TextureDownloader::getInstance() {
    s_createMutex.lock();
        if(s_instance == nullptr)
        {
            s_instance = new TextureDownloader();
        }
    s_createMutex.unlock();
    return s_instance;
}


void TextureDownloader::download(QUrl url, QString destination, std::shared_ptr<Texture> t) {
    DownloadTask* dt = new DownloadTask(url, destination, t); 
    m_pending.push(dt);
}


void TextureDownloader::flushPending() {
    m_takeMutex.lock();
        while(!m_pending.empty())
            m_pending.pop();
    m_takeMutex.unlock();
}


void TextureDownloader::finishedEvent(QNetworkReply* reply) {
    DownloadTask* dt = m_active[reply->url()];

    qint64 size = reply->bytesAvailable();
    char *buffer = new char[size];

    qint64 bytes_read = reply->read(buffer, size);

    QFile f(dt->getFilename());
    int err = f.open(QIODevice::WriteOnly);
    if (size != 0 && bytes_read == size && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200 && err) {
        f.write(buffer, size);
        f.close();
        dt->getTexture()->loadFromFile(dt->getFilename().toStdString());
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
