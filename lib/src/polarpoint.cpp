#include "polarpoint.h"
#define _USE_MATH_DEFINES
#include <math.h>
PolarPoint::PolarPoint(qreal r, qreal theta, qreal phi)
{
    m_r = r;
    m_theta = theta;
    m_phi = phi;
}

PolarPoint::PolarPoint(const QVector3D &source)
{
    m_r = sqrt(
                     (source.x()*source.x())
                    +(source.y()*source.y())
                    +(source.z()*source.z())
                );
    m_theta = acos(source.z()/m_r);
    m_phi = atan2(source.y(),source.x());
}

qreal
PolarPoint::pan()
{
    return m_theta * 180 / M_PI;
}

qreal
PolarPoint::tilt()
{
    return m_phi * 180 / M_PI;
}
