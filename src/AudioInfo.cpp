#include "AudioInfo.h"

AudioInfo::AudioInfo(QObject *parent)
    : QObject{parent}
{

}

int AudioInfo::songIndex() const
{
    return m_songIndex;
}

void AudioInfo::setSongIndex(int newSongIndex)
{
    if (m_songIndex == newSongIndex)
        return;
    m_songIndex = newSongIndex;
    emit songIndexChanged();
}

QString AudioInfo::songName() const
{
    return m_songName;
}

void AudioInfo::setSongName(const QString &newSongName)
{
    if (m_songName == newSongName)
        return;
    m_songName = newSongName;
    emit songNameChanged();
}

QString AudioInfo::authorName() const
{
    return m_authorName;
}

void AudioInfo::setAuthorName(const QString &newAuthorName)
{
    if (m_authorName == newAuthorName)
        return;
    m_authorName = newAuthorName;
    emit authorNameChanged();
}

QUrl AudioInfo::songImg() const
{
    return m_songImg;
}

void AudioInfo::setSongImg(const QUrl &newSongImg)
{
    if (m_songImg == newSongImg)
        return;
    m_songImg = newSongImg;
    emit songImgChanged();
}

QUrl AudioInfo::songUrl() const
{
    return m_songUrl;
}

void AudioInfo::setSongUrl(const QUrl &newSongUrl)
{
    if (m_songUrl == newSongUrl)
        return;
    m_songUrl = newSongUrl;
    emit songUrlChanged();
}

int AudioInfo::duration() const
{
    return m_duration;
}

void AudioInfo::setDuration(int newDuration)
{
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    emit durationChanged();
}
