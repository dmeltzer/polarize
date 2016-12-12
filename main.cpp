#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QVector3D>
#define _USE_MATH_DEFINES
#include <math.h>
class PolarPoint
{
    public:
    qreal r;
    qreal theta;
    qreal phi;

    qreal pan()
    {
        return theta*180/M_PI;
    }

    qreal tilt()
    {
        return phi*180/M_PI;
    }

  operator QString() const { return QString("R: %1 Theta: %2 Phi: %3").arg(r).arg(theta).arg(phi); }
};

PolarPoint toPolar(const QVector3D &source)
{
    PolarPoint ret;
    ret.r = sqrt(
                     (source.x()*source.x())
                    +(source.y()*source.y())
                    +(source.z()*source.z())
                );
    ret.theta = acos(source.z()/ret.r);
    ret.phi = atan2(source.y(),source.x());
    return ret;
}

QVector3D inputPoint(const QString &name)
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
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    while(true) {
        QVector3D targetPoint = inputPoint("Target");
        QVector3D sourcePoint = inputPoint("Source");

        //    // antonfire@freenode##math> so work out the cartesian coordinates of that vector,
        //    // and convert them to spherical coordinates the standard way that
        //    // you can find (and find an explanation of) by googling "spherical coordinates".
        //    // Calibration Pan & Tilt:
        // Calcualte the vector from source to target.
        QVector3D calculatedVector = targetPoint - sourcePoint;
        qDebug() << "vector: " << calculatedVector;
        PolarPoint panTilt = toPolar(calculatedVector);

        qDebug() << "Pan: " << panTilt.pan() << " Tilt: " << panTilt.tilt();

    }
    return a.exec();
}




