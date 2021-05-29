#pragma once

#include <queue>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

#include <Data/vectortiledata.h>

class DataDownloadTask : public QObject
{
    Q_OBJECT
private:

    QUrl m_url;
    QString m_filename;
    std::shared_ptr<VectorTileData> m_data;

    QNetworkReply* m_reply;

public:
    DataDownloadTask(QUrl url, QString filename, std::shared_ptr<VectorTileData>& t);
    void start(QNetworkAccessManager* manager);

    QUrl getUrl() { return m_url; };
    QString getFilename() { return m_filename; };
    std::shared_ptr<VectorTileData>& getData() { return m_data; };
};

class VectorTileDataDownloader : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager* m_manager;
    std::queue<DataDownloadTask*> m_pending;
    std::map<QUrl, DataDownloadTask*> m_active;

    QMutex m_takeMutex;

    static VectorTileDataDownloader* s_instance;
    static QMutex s_createMutex;

public:
    virtual ~VectorTileDataDownloader();

    static VectorTileDataDownloader* getInstance();

    void download(QUrl url, QString destination, std::shared_ptr<VectorTileData> t);
    void update();
    void flushPending();

private:
    VectorTileDataDownloader();

    void run();

public slots:
    void finishedEvent(QNetworkReply* reply);

};
