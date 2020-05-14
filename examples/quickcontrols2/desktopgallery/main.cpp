#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2/qquickstyle.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // Todo: rename the "default" style to e.g "simple"
    // and use "default" as a phony style name instad
    // to mean "get me the default style on the current
    // platform".
    const QString style = qEnvironmentVariable("DESKTOPGALLERY_STYLE");
    if (!style.isEmpty())
        QQuickStyle::setStyle(style);
    else
#if defined(Q_OS_OSX)
        QQuickStyle::setStyle("macOS");
#elif defined(Q_OS_WINDOWS)
        QQuickStyle::setStyle("Windows");
#else
        QQuickStyle::setStyle("FusionDesktop");
#endif

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
