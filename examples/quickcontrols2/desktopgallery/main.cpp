#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2/qquickstyle.h>

int main(int argc, char *argv[])
{
#ifdef Q_OS_OSX
    // Todo: rename the "default" style to e.g "simple"
    // and use "default" as a phony style name instad
    // to mean "get me the default style on the current
    // platform".
    QQuickStyle::setStyle("macos");
#endif

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
