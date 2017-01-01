#ifndef POLARPOINT_H
#define POLARPOINT_H
#include <QVector3D>
#include <QString>

#include "polarize-lib_global.h"

class POLARIZELIBSHARED_EXPORT PolarPoint
{
public:
    PolarPoint();
    PolarPoint(qreal r, qreal theta, qreal phi);
    PolarPoint(const QVector3D &);

    void setR(qreal r) { m_r = r; }
    void setTheta(qreal theta) { m_theta = theta; }
    void setPhi( qreal phi ) { m_phi = phi; }

    qreal pan();
    qreal tilt();


    operator QString() const { return QString("R: %1 Theta: %2 Phi: %3").arg(m_r).arg(m_theta).arg(m_phi); }
private:
    qreal m_r; // Radius, distance from point to point in a straight line
    qreal m_theta; // Azumith coordinate.  Represents Pan.
    qreal m_phi; // Inclination Coordinate.  Represents tilt
};

#endif // POLARPOINT_H
