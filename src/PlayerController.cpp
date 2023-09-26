#include "PlayerController.h"

PlayerController::PlayerController(QObject *parent)
    : QAbstractListModel{parent}
{
    connect(&m_mediaPlayer,&QMediaPlayer::positionChanged,this,&PlayerController::positionChangedSlot) ;

    QList<AudioInfo*> listFromDb ;
    m_localDb.getSongList(listFromDb) ;

    if(!listFromDb.isEmpty()){
        foreach (auto element, listFromDb) {
            this->addAudio(element->songName(), element->authorName(), element->songUrl()
                           , element->songImg(), element->duration()) ;
        }
    }

    qDeleteAll(listFromDb) ;
    listFromDb.clear() ;
}

bool PlayerController::playing() const
{
    return m_playing;
}

void PlayerController::playPreviousSong()
{
    if(!m_currentSong) return ;

    int index = m_audioList.indexOf(m_currentSong) ;

    if(index > 0){
        setCurrentSong(m_audioList[index-1]) ;
    }
    else{
        setCurrentSong(m_audioList[m_audioList.length() - 1]) ;
    }
}

void PlayerController::playPause()
{
    m_playing = !m_playing ;

    if(m_playing){
        m_mediaPlayer.play() ;
    }
    else {
        m_mediaPlayer.pause() ;
    }

    emit playingChanged() ;
}

void PlayerController::playNextSong()
{
    if(!m_currentSong) return ;

    int index = m_audioList.indexOf(m_currentSong) ;

    if(index + 1 >= m_audioList.length()){
        setCurrentSong(m_audioList[0]) ;
    }
    else{
        setCurrentSong(m_audioList[index+1]) ;
    }
}

void PlayerController::changedAudioSource(const QUrl &a_url)
{
    m_mediaPlayer.stop() ;
    m_mediaPlayer.setAudioRole(QAudio::MusicRole) ;
    m_mediaPlayer.setMedia(a_url) ;

    if(playing()){
        m_mediaPlayer.play() ;
    }
}

void PlayerController::addAudio(const QString &title, const QString &author, const QUrl &songSource, const QUrl &imgSource, const int &duration)
{
    if(m_urlSet.contains(songSource))
        return ;

    beginInsertRows(QModelIndex(), m_audioList.length(), m_audioList.length()) ;

    AudioInfo *audio = new AudioInfo(this) ;
    audio->setSongName(title) ;
    audio->setAuthorName(author) ;
    audio->setSongUrl(songSource) ;
    audio->setSongImg(imgSource) ;
    audio->setDuration(duration) ;

    if(m_audioList.isEmpty()) setCurrentSong(audio) ;

    m_audioList.append(audio) ;
    m_urlSet.insert(songSource) ;
    m_localDb.insertSong(songSource.toString(), imgSource.toString(), title, author, duration) ;

    endInsertRows() ;
}

void PlayerController::removeAudio(int index)
{
    if(index >= 0 && index < m_audioList.length()){

        beginRemoveRows(QModelIndex(), index, index) ;

        AudioInfo *toRemove = m_audioList[index] ;

        if(toRemove == m_currentSong){
            if(m_audioList.length() > 1){
                if(index != 0){
                    setCurrentSong(m_audioList[index-1]) ;
                }
                else{
                    setCurrentSong(m_audioList[index+1]) ;
                }
            }
            else{
                setCurrentSong(nullptr) ;
            }
        }

        m_localDb.removeSong(m_audioList[index]->songUrl().toString()) ;
        m_urlSet.remove(m_audioList[index]->songUrl()) ;
        m_audioList.removeAt(index) ;
        toRemove->deleteLater() ;

        endRemoveRows() ;
    }

}

void PlayerController::switchToAudioByIndex(int index)
{
    if(index >= 0 && index < m_audioList.length()){
        setCurrentSong(m_audioList[index]) ;
    }
}

void PlayerController::positionChangedSlot()
{
    setSliderPosition(m_mediaPlayer.position()/1000) ;
}

void PlayerController::moveSlider(int position)
{
    m_mediaPlayer.setPosition(position*1000) ;
}

int PlayerController::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent) ;
    return m_audioList.length() ;
}

QVariant PlayerController::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.row() >= 0 && index.row() < m_audioList.length()){

        AudioInfo *audioInfo = m_audioList[index.row()] ;

        switch((Role) role){
        case AudioAuthorNameRole:
            return audioInfo->authorName() ;
        case AudioTitleRole :
            return audioInfo->songName() ;
        case AudioSourceRole :
            return audioInfo->songUrl() ;
        case AudioImageSourceRole :
            return audioInfo->songImg() ;
        case AudioDurationRole :
            return audioInfo->duration() ;
        }

    }

    return {} ;
}

QHash<int, QByteArray> PlayerController::roleNames() const
{
    QHash<int, QByteArray> result ;

    result[AudioAuthorNameRole] = "audioAuthorName" ;
    result[AudioTitleRole] = "audioTitle" ;
    result[AudioSourceRole] = "audioSource" ;
    result[AudioImageSourceRole] = "audioImageSource" ;
    result[AudioDurationRole] = "audioDuration" ;

    return result ;
}

AudioInfo *PlayerController::currentSong() const
{
    return m_currentSong;
}

void PlayerController::setCurrentSong(AudioInfo *newCurrentSong)
{
    if (m_currentSong == newCurrentSong)
        return;
    m_currentSong = newCurrentSong;
    emit currentSongChanged();

    if(m_currentSong){
        changedAudioSource(m_currentSong->songUrl()) ;
    }
    else{
        m_mediaPlayer.stop() ;
        m_mediaPlayer.setMedia(QUrl("")) ;
        m_playing = false ;
        emit playingChanged() ;
    }
}

int PlayerController::sliderPosition() const
{
    return m_sliderPosition;
}

void PlayerController::setSliderPosition(int newSliderPosition)
{
    if (m_sliderPosition == newSliderPosition)
        return;
    m_sliderPosition = newSliderPosition;
    emit sliderPositionChanged();
}
