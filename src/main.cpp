#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

#include "PlayerController.h"
#include "AudioInfo.h"
#include "AudioSearchModel.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon("://images/app_icon.png")) ;

    QQmlApplicationEngine engine;

    PlayerController *playerController = new PlayerController(&app) ;
    qmlRegisterSingletonInstance("com.company.PlayerController",1,0,"PlayerController",playerController) ;

    AudioSearchModel *audioSearchModel = new AudioSearchModel(&app) ;
    qmlRegisterSingletonInstance("com.company.AudioSearchModel",1,0,"AudioSearchModel",audioSearchModel) ;

    qmlRegisterType<AudioInfo>("com.company.AudioInfo",1,0,"AudioInfo") ;

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
