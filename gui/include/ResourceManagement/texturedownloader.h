#pragma once

#include <queue>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

#include <OpenGL/texture.h>

class DownloadTask : public QObject
{
    Q_OBJECT
private:

    QUrl m_url;
    QString m_filename;
    std::shared_ptr<Texture> m_texture;

    QNetworkReply* m_reply;

public:
    DownloadTask(QUrl url, QString filename, std::shared_ptr<Texture> t);
    void start(QNetworkAccessManager* manager);

    QUrl getUrl() { return m_url; };
    QString getFilename() { return m_filename; };
    std::shared_ptr<Texture> getTexture() { return m_texture; };
};

class TextureDownloader : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager* m_manager;
    std::queue<DownloadTask*> m_pending;
    std::map<QUrl, DownloadTask*> m_active;

    QMutex m_takeMutex;

    static TextureDownloader* s_instance;
    static QMutex s_createMutex;

public:
    virtual ~TextureDownloader();

    static TextureDownloader* getInstance();

    void download(QUrl url, QString destination, std::shared_ptr<Texture> t);
    void update();
    void flushPending();

private:
    TextureDownloader();

    void run();

public slots:
    void finishedEvent(QNetworkReply* reply);

};
