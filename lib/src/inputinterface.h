#ifndef POLARIZE_INPUTINTERFACE_H
#define POLARIZE_INPUTINTERFACE_H
#include <QVector3D>
#include <QtPlugin>
class PolarizeInputInterface
{
public:
    virtual ~PolarizeInputInterface() {}
    virtual QVector3D inputValues(const QString &name) = 0;
};

#define POLAR_INPUTINTERFACE_iid "org.dmeltzer.polarize.TerminalInput"
Q_DECLARE_INTERFACE(PolarizeInputInterface, POLAR_INPUTINTERFACE_iid)
#endif // POLARIZE_INPUTINTERFACE_H
