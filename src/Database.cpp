#include "Database.h"
#include "AudioInfo.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDebug>
#include <QUrl>

Database::Database(QObject *parent)
    : QObject{parent}
{
    m_dbpath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) ;

    m_localdb = QSqlDatabase::addDatabase("QSQLITE") ;
    m_localdb.setDatabaseName(m_dbpath) ;

    if(!m_localdb.open()){
        qCritical() << "Could not open" << m_localdb.lastError() ;
    }

    this->createTables() ;

}

Database::~Database()
{
    m_localdb.close() ;
}

void Database::insertSong(QString a_songUrl, QString a_imgUrl, QString a_songName, QString a_authorName, int a_duration)
{
    QSqlQuery query(m_localdb) ;
    query.prepare("INSERT INTO song_table(song_url, img_url, song_name, author_name, duration) "
                  "VALUES(:song_url, :img_url, :song_name, :author_name, :duration)") ;
    query.bindValue(":song_url", a_songUrl) ;
    query.bindValue(":img_url", a_imgUrl) ;
    query.bindValue(":song_name", a_songName) ;
    query.bindValue(":author_name", a_authorName) ;
    query.bindValue(":duration", a_duration) ;

    if(!query.exec()){
        qCritical() << "Couldn't insert song " << query.lastError() ;
    }
}

void Database::getSongList(QList<AudioInfo *> &a_audioList)
{
    a_audioList.clear() ;

    QSqlQuery query(m_localdb) ;
    query.prepare("SELECT * FROM song_table") ;

    if(!query.exec()){
        qCritical() << "Couldn't get song list" << query.lastError() ;
    }

    while(query.next()){
        QUrl songUrl = query.value(0).toUrl() ;
        QUrl imgUrl = query.value(1).toUrl() ;
        QString songName = query.value(2).toString() ;
        QString authorName = query.value(3).toString() ;
        int duration = query.value(4).toInt() ;

        AudioInfo *song = new AudioInfo() ;
        song->setSongUrl(songUrl) ;
        song->setSongImg(imgUrl) ;
        song->setSongName(songName) ;
        song->setAuthorName(authorName) ;
        song->setDuration(duration) ;

        a_audioList.append(song) ;
    }
}

void Database::removeSong(QString a_songUrl)
{
    QSqlQuery query(m_localdb) ;
    query.prepare("DELETE FROM song_table WHERE song_url = :song_url") ;
    query.bindValue(":song_url", a_songUrl) ;

    if(!query.exec()){
        qCritical() << "couldn't remove song" << query.lastError() ;
    }
}

void Database::createTables()
{
    QSqlQuery query(m_localdb) ;
    query.prepare("CREATE TABLE IF NOT EXISTS song_table(song_url TEXT NOT NULL PRIMARY KEY, img_url TEXT, "
                  "song_name TEXT, author_name TEXT, duration INT)") ;

    if(!query.exec()){
        qCritical() << "Couldn't create table" << query.lastError() ;
    }
}
