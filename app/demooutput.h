#ifndef DEMOOUTPUT_H
#define DEMOOUTPUT_H

#include <QObject>
#include <QDebug>
#include <QJSValue>
#include "src/polarpoint.h"
class DemoOutput : public QObject
{
    Q_OBJECT
public:
    explicit DemoOutput(QObject *parent = 0);
    Q_INVOKABLE void output(const QStringList &source, const QStringList &target);

signals:

public slots:
    void calculate(const QVariant &source, const QVariant &target) {
        qDebug() << source << " and " << target;
//        QVariantList list = source;
    }
};

#endif // DEMOOUTPUT_H
