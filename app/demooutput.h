#ifndef DEMOOUTPUT_H
#define DEMOOUTPUT_H

#include <QObject>
#include <QDebug>
#include <QJSValue>
#include "src/polarpoint.h"
class DemoOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal pan READ pan WRITE setPan NOTIFY panChanged)

    Q_PROPERTY(qreal tilt READ tilt WRITE setTilt NOTIFY tiltChanged)
public:
    explicit DemoOutput(QObject *parent = 0);
    Q_INVOKABLE void output(const QStringList &source, const QStringList &target);
    qreal pan() { return m_pan; }
    void setPan(qreal pan ) { if(m_pan != pan) m_pan = pan; emit panChanged(); }
    qreal tilt() { return m_tilt; }
    void setTilt(qreal tilt) {if(m_tilt !=tilt) m_tilt = tilt; emit tiltChanged(); }

signals:
    void panChanged();
    void tiltChanged();

public slots:
    void calculate(const QVariant &source, const QVariant &target) {
        qDebug() << source << " and " << target;
//        QVariantList list = source;
    }

private:
    qreal m_pan;
    qreal m_tilt;
};

#endif // DEMOOUTPUT_H
