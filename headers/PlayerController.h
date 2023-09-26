#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAbstractListModel>
#include <QSet>

#include "AudioInfo.h"
#include "Database.h"

class PlayerController : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool playing READ playing  NOTIFY playingChanged)
    Q_PROPERTY(AudioInfo* currentSong READ currentSong WRITE setCurrentSong NOTIFY currentSongChanged)
    Q_PROPERTY(int sliderPosition READ sliderPosition WRITE setSliderPosition NOTIFY sliderPositionChanged)

public:
    explicit PlayerController(QObject *parent = nullptr);
    
    enum Role{
        AudioAuthorNameRole = Qt::UserRole + 1 ,
        AudioTitleRole,
        AudioSourceRole,
        AudioImageSourceRole,
        AudioDurationRole
    };

    bool playing() const;
    void setCurrentSong(AudioInfo *newCurrentSong);
    AudioInfo* currentSong() const ;

public slots:

    void playPreviousSong() ;
    void playPause() ;
    void playNextSong() ;
    void changedAudioSource(const QUrl &a_url) ;
    void addAudio(const QString &title, const QString &author, const QUrl &songSource, const QUrl &imgSource, const int &Duration) ;
    void removeAudio(int index);
    void switchToAudioByIndex(int index);
    void positionChangedSlot() ;
    void moveSlider(int position) ;

signals:
    void playingChanged();
    void currentSongChanged() ;
    void sliderPositionChanged();

private:
    bool m_playing = false;
    QMediaPlayer m_mediaPlayer ;
    QList<AudioInfo*> m_audioList ;
    AudioInfo *m_currentSong = nullptr ;
    int m_sliderPosition;
    QSet<QUrl> m_urlSet ;
    Database m_localDb ;

public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    int sliderPosition() const;
    void setSliderPosition(int newSliderPosition);
};

#endif // PLAYERCONTROLLER_H
