#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>

class AudioInfo ;

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database() ;

    void insertSong(QString a_songUrl, QString a_imgUrl, QString a_songName, QString a_authorName, int a_duration) ;
    void getSongList(QList<AudioInfo*> &a_audioList) ;
    void removeSong(QString a_songUrl) ;

private:
    QSqlDatabase m_localdb ;
    QString      m_dbpath ;

    void createTables() ;

signals:

};

#endif // DATABASE_H
