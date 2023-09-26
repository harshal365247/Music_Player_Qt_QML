#ifndef AUDIOSEARCHMODEL_H
#define AUDIOSEARCHMODEL_H

#include <QAbstractListModel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

#include "AudioInfo.h"

class AudioSearchModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool isSearching READ isSearching WRITE setIsSearching NOTIFY isSearchingChanged)
public:
    explicit AudioSearchModel(QObject *parent = nullptr);

    enum Role{
        AudioAuthorNameRole = Qt::UserRole + 1 ,
        AudioTitleRole,
        AudioSourceRole,
        AudioImageSourceRole,
        AudioDurationRole
    };

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool isSearching() const;
    void setIsSearching(bool newIsSearching);

public slots:
    void searchSong(const QString& name) ;
    void parseData() ;

signals:
    void isSearchingChanged();

private:
    QList<AudioInfo*> m_audioList ;
    QNetworkAccessManager m_networkManager ;
    QNetworkReply *m_reply = nullptr ;
    QString m_requestUrl ;
    QString m_clientID ;
    bool m_isSearching = false;
};

#endif // AUDIOSEARCHMODEL_H
