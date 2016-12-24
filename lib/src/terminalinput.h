#ifndef TERMINALINPUT_H
#define TERMINALINPUT_H

#include "inputinterface.h"
#include <QObject>

class TerminalInput : public QObject, PolarizeInputInterface
{
    Q_OBJECT
//    Q_PLUGIN_METADATA(IID POLAR_INPUTINTERFACE_IID)
    Q_INTERFACES(PolarizeInputInterface)

public:
    TerminalInput();

    QVector3D inputValues(const QString &name) Q_DECL_OVERRIDE;
};

#endif // TERMINALINPUT_H
