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

#include "demooutput.h"

#include <QHostAddress>
DemoOutput::DemoOutput(QObject *parent)
    : QObject(parent)
    , m_pan(0)
    , m_tilt(0)
    , m_channel(1)
    , m_ipAddress(QString("127.0.0.1"))
    , m_oscEnabled(false)
    , m_manager(0)
{
    m_manager = new OSCNetworkManager;
    m_manager->setIpAddress(QHostAddress(m_ipAddress));
    m_manager->setUseTcp(true);
    m_manager->setEnabled(true);
}

void
DemoOutput::output(const QStringList &source, const QStringList &target)
{
    if(!m_oscEnabled) {
        qDebug() << "Output not enabled, aborting";
        return;
    }

    // Okay, so lets take this step by step.
    // Three points:
    // Point of The light source itself.  This will be shifted to 0,0,0
    // "Home" Point for the light.  This will start as 0,0,0, but be shifted by the z of the light. Immediately below the point of the light
    // Target we are pointing at.
    QVector3D sourcePoint(source[0].toFloat(), source[1].toFloat(), source[2].toFloat());
    QVector3D calibrationPoint(source[0].toFloat(), source[1].toFloat(), 0);
    QVector3D targetPoint(target[0].toFloat(), target[1].toFloat(), target[2].toFloat());

    qDebug() << "Source: " << sourcePoint << " Origin: " << calibrationPoint << " Target: " << targetPoint;

    // We need to shift the source to 0.  This means we should subtract the source from each vector.
    QVector3D translatedSource = sourcePoint - sourcePoint;
    QVector3D translatedOrigin = calibrationPoint - sourcePoint;
    QVector3D translatedTarget = targetPoint - sourcePoint;

    qDebug() << "Translated: ";
    qDebug() << "Source: " << translatedSource << " Origin: " << translatedOrigin << " Target: " << translatedTarget;

    // Now lets polarize the calibartion point -- And calculate the pan/tilt to it.  This should be 0,0 if things are working.
    PolarPoint p_Origin(translatedOrigin);
    qDebug() << "ORIGIN: Pan: " << p_Origin.pan() << "Tilt: " << p_Origin.tilt();


    // Polarize the target point and calculate source between the two.
    PolarPoint p_translated(translatedTarget);

    // Todo, separate a point and a vector into separate classes.
    PolarPoint translatedVector = p_Origin.toPoint(p_translated);
    qDebug() << "TARGET: Pan: " << translatedVector.pan() << "Tilt: " << translatedVector.tilt();

    setPan(translatedVector.pan());
    const QString panCmd = QString("/eos/user/0/chan/%1/param/pan=%2").arg(m_channel).arg(translatedVector.pan());
    m_manager->sendMessage(panCmd);

    const QString tiltCmd = QString("/eos/user/0/chan/%1/param/tilt=%2").arg(m_channel).arg(translatedVector.tilt());
    m_manager->sendMessage(tiltCmd);
    setTilt(translatedVector.tilt());
}

void
DemoOutput::setIpAddress(QString ipAddress)
{
    if(m_ipAddress!=ipAddress) {
        qDebug() << "IP Changed: " << ipAddress;
        m_ipAddress = ipAddress;
        m_manager->setIpAddress(QHostAddress(ipAddress));
    }
    emit ipChanged();
}
