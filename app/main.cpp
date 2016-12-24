#include <QApplication>
#include <QDebug>
#include <QVector3D>
#include <QDir>
#include <QQmlApplicationEngine>
#include "src/polarpoint.h"
#include <QSettings>
#include <QRect>
#include <QQuickWindow>
#include <QQmlContext>
#include "demooutput.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QQmlApplicationEngine *engine = new QQmlApplicationEngine();

    DemoOutput *d = new DemoOutput;
    engine->rootContext()->setContextProperty("_demo", d);
    // actually load QML file:
    engine->load(QUrl(QStringLiteral("/Users/parallelgrapefruit/work/polarize/app/mainwindow.qml")));
    QSettings independentSettings;

    QRect windowGeometry = independentSettings.value("windowGeometry").toRect();
    bool maximized = independentSettings.value("maximized").toBool();
    QQuickWindow* window = qobject_cast<QQuickWindow*>(engine->rootObjects()[0]);
//    qDebug() << window;
//    QObject::connect(window, SIGNAL(calculate(QVariant, QVariant)), d, SLOT(calculate(QVariant,QVariant)));
    if (!window) return 0;
    if (!windowGeometry.isNull()) window->setGeometry(windowGeometry);
    if (maximized) window->showMaximized();
    return a.exec();
}



