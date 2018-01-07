/***************************************************************************
** Polarize Positioning                                                   **
**                                                                        **
** Copyright (C) 2016-2017  Daniel Meltzer <dmeltzer.devel@gmail.com>     **
**                                                                        **
** This program is free software; you can redistribute it and/or modify   **
** it under the terms of the GNU General Public License as published by   **
** the Free Software Foundation; either version 3 of the License, or      **
** (at your option) any later version.                                    **
** This program is distributed in the hope that it will be useful,        **
** but WITHOUT ANY WARRANTY; without even the implied warranty of         **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          **
** GNU General Public License for more details.                           **
** You should have received a copy of the GNU General Public License      **
** along with this program; if not, write to the Free Software Foundation,**
** Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA      **
***************************************************************************/

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

PolarPoint
PolarPoint::toPoint(const PolarPoint &point)
{
    // Pan will be phi_cal - phi_trans
    qreal newPhi = phi() - point.phi();
    // Tilt will be theta_cal - theta_trans
    qreal newTheta = theta() - point.theta();
    // R will be r_cal - r_trans
    qreal newR = R() - point.R();
    return PolarPoint(newR, newTheta, newPhi);
}
