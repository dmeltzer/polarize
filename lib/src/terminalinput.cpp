#include "terminalinput.h"

#include <QTextStream>
#include <QStringList>
#include <QDebug>
TerminalInput::TerminalInput()
{

}

QVector3D
TerminalInput::inputValues(const QString &name)
{
    QTextStream stream(stdin);
    QString input;
    qDebug() << QString("Enter %1 Values as x,y,z").arg(name);
    while(stream.readLineInto(&input))
    {
        const QStringList values = input.split(',');
        if(values.count() != 3) {
            qDebug() << "Invalid Format, Please try again";
            continue;
        }
        return QVector3D(values[0].toFloat(),values[1].toFloat(),values[2].toFloat());
    }
    return QVector3D();
}
