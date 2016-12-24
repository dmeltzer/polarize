#include "demooutput.h"

DemoOutput::DemoOutput(QObject *parent)
    : QObject(parent)
    , m_pan(0)
    , m_tilt(0)
{


//    bool
//    MainApp::loadPlugins()
//    {
//        QDir pluginsDir(qApp->applicationDirPath());
//        #if defined(Q_OS_WIN)
//            if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
//                pluginsDir.cdUp();
//        #elif defined(Q_OS_MAC)
//            if (pluginsDir.dirName() == "MacOS") {
//                pluginsDir.cdUp();
//                pluginsDir.cdUp();
//                pluginsDir.cdUp();
//            }
//        #endif
//            pluginsDir.cd("plugins");
//            foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
//                QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
//                QObject *plugin = pluginLoader.instance();
//                if (plugin) {
//                    m_input = qobject_cast<PolarizeInputInterface *>(plugin);
//                    if (m_input)
//                        return true;
//                }
//            }

//            return false;
//    }
}

void
DemoOutput::output(const QStringList &source, const QStringList &target)
{
    qDebug() << "TRIGERED: " << source << " TARGET: " << target;
    QVector3D sourcePoint(source[0].toFloat(), source[1].toFloat(), source[2].toFloat());
    QVector3D targetPoint(target[0].toFloat(), target[1].toFloat(), target[2].toFloat());

    QVector3D calculatedVector = targetPoint - sourcePoint;

    PolarPoint dest(calculatedVector);
    setPan(dest.pan());
    setTilt(dest.tilt());
    qDebug() << "Pan: " << dest.pan() << "Tilt: " << dest.tilt();
}
