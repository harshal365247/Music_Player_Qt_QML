#ifndef AUDIOINFO_H
#define AUDIOINFO_H

#include <QObject>
#include <QUrl>
#include <qqml.h>

class AudioInfo : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit AudioInfo(QObject *parent = nullptr);

    Q_PROPERTY(int songIndex READ songIndex WRITE setSongIndex NOTIFY songIndexChanged REQUIRED)
    Q_PROPERTY(QString songName READ songName WRITE setSongName NOTIFY songNameChanged)
    Q_PROPERTY(QString authorName READ authorName WRITE setAuthorName NOTIFY authorNameChanged)
    Q_PROPERTY(QUrl songImg READ songImg  WRITE setSongImg NOTIFY songImgChanged)
    Q_PROPERTY(QUrl songUrl READ songUrl WRITE setSongUrl NOTIFY songUrlChanged REQUIRED)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)

    int songIndex() const;
    void setSongIndex(int newSongIndex);

    QString songName() const;
    void setSongName(const QString &newSongName);

    QString authorName() const;
    void setAuthorName(const QString &newAuthorName);

    QUrl songImg() const;
    void setSongImg(const QUrl &newSongImg);

    QUrl songUrl() const;
    void setSongUrl(const QUrl &newSongUrl);

    int duration() const;
    void setDuration(int newDuration);

signals:

    void songIndexChanged();
    void songNameChanged();
    void authorNameChanged();
    void songImgChanged();
    void songUrlChanged();

    void durationChanged();

private:
    int m_songIndex;
    QString m_songName;
    QString m_authorName;
    QUrl m_songImg;
    QUrl m_songUrl;
    int m_duration;
};

#endif // AUDIOINFO_H
