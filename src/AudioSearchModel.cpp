#include "AudioSearchModel.h"

#include <QUrlQuery>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

AudioSearchModel::AudioSearchModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_requestUrl = "https://api.jamendo.com/v3.0/tracks/" ;
    m_clientID = "d2448839" ;
    connect(&m_networkManager, &QNetworkAccessManager::finished, this, &AudioSearchModel::parseData) ;
}

int AudioSearchModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_audioList.length() ;
}

QVariant AudioSearchModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.row() >= 0 && index.row() < m_audioList.length()){
        switch (role) {
        case AudioAuthorNameRole:
            return m_audioList[index.row()]->authorName() ;
        case AudioTitleRole:
            return m_audioList[index.row()]->songName() ;
        case AudioImageSourceRole:
            return m_audioList[index.row()]->songImg() ;
        case AudioSourceRole:
            return m_audioList[index.row()]->songUrl() ;
        case AudioDurationRole:
            return m_audioList[index.row()]->duration() ;
        }
    }

    return {} ;
}

QHash<int, QByteArray> AudioSearchModel::roleNames() const
{
    QHash<int, QByteArray> result ;

    result[AudioAuthorNameRole] = "audioAuthorName" ;
    result[AudioTitleRole] = "audioTitle" ;
    result[AudioSourceRole] = "audioSource" ;
    result[AudioImageSourceRole] = "audioImageSource" ;
    result[AudioDurationRole] = "audioDuration" ;

    return result ;
}

void AudioSearchModel::searchSong(const QString &name){

    if(!name.trimmed().isEmpty()){
        if(m_reply){
            m_reply->abort() ;
            m_reply->deleteLater() ;
            m_reply = nullptr ;
        }

        QUrlQuery urlQuery ;

        urlQuery.addQueryItem("client_id", m_clientID) ;
        urlQuery.addQueryItem("name", name) ;
        urlQuery.addQueryItem("format", "json") ;

        setIsSearching(true) ;
        m_reply = m_networkManager.get(QNetworkRequest(m_requestUrl + "?" + urlQuery.toString())) ;
    }
}

void AudioSearchModel::parseData(){

    if(m_reply->error() == QNetworkReply::NoError){

        qDeleteAll(m_audioList) ;
        m_audioList.clear() ;

        beginResetModel() ;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(m_reply->readAll()) ;
        QJsonObject headersObj = jsonDoc["headers"].toObject() ;

        if(headersObj["error_message"].toString().isEmpty() && headersObj["status"].toString() == "success" ){
            QJsonArray results = jsonDoc["results"].toArray() ;

            for(const auto &result : results){

                QJsonObject resultObj = result.toObject() ;

                if(resultObj["audiodownload_allowed"].toBool()){

                    AudioInfo *audioinfo = new AudioInfo(this) ;
                    audioinfo->setSongName(resultObj["name"].toString()) ;
                    audioinfo->setAuthorName(resultObj["artist_name"].toString()) ;
                    audioinfo->setSongImg(resultObj["image"].toString()) ;
                    audioinfo->setSongUrl(resultObj["audiodownload"].toString()) ;
                    audioinfo->setDuration(resultObj["duration"].toInt()) ;

                    m_audioList.append(audioinfo) ;
                }
            }
        }
        else{
            qCritical() << headersObj["error_message"].toString() ;
        }

        endResetModel() ;

    }
    else if(m_reply->error() == QNetworkReply::OperationCanceledError){
        qCritical() << m_reply->errorString() ;
    }

    setIsSearching(false) ;
    m_reply->deleteLater() ;
    m_reply = nullptr ;
}

bool AudioSearchModel::isSearching() const
{
    return m_isSearching;
}

void AudioSearchModel::setIsSearching(bool newIsSearching)
{
    if (m_isSearching == newIsSearching)
        return;
    m_isSearching = newIsSearching;
    emit isSearchingChanged();
}
