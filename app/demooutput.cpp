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
    , m_currentLocation(0,0,0)
{
    m_manager = new OSCNetworkManager;
    m_manager->setIpAddress(QHostAddress(m_ipAddress));
    m_manager->setUseTcp(true);
    m_manager->setEnabled(true);

    connect(m_manager, SIGNAL(messageReceived(OSCMessage)), this, SLOT(onMessageRecieved(OSCMessage)));
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
    // Calibration point.  This is where the light currently is.
    // Target we are pointing at.

    QVector3D sourcePoint(source[0].toFloat(), source[1].toFloat(), source[2].toFloat());
    QVector3D targetPoint(target[0].toFloat(), target[1].toFloat(), target[2].toFloat());

    if(sourcePoint == targetPoint) {
        qDebug() << "No Change in values, ignoring";
        return;
    }
    qDebug() << "Source: " << sourcePoint << " Target: " << targetPoint;

    // We need to shift the source to 0.  This means we should subtract the source from each vector.
    QVector3D translatedSource = sourcePoint - sourcePoint;
    QVector3D translatedTarget = targetPoint - sourcePoint;

    qDebug() << "Translated: ";
    qDebug() << "Source: " << translatedSource << " Target: " << translatedTarget;


    // Now lets calculate pan/tilt to the calibartion point -- And calculate the pan/tilt to it.  This should be current pan/tilt if things are working.
//    PolarPoint p_current = PolarPoint(sourcePoint).toPoint(m_currentLocation);
    PolarPoint p_current = m_currentLocation.toPoint(PolarPoint(sourcePoint));
    qDebug() << "ORIGIN: Pan: " << p_current.pan() << "Tilt: " << p_current.tilt();


    // Polarize the target point and calculate source between the two.
    PolarPoint p_translated(translatedTarget);

    // This generates the adjustments in pan and tilt we need to make to the current location.
    PolarPoint translatedVector = m_currentLocation.toPoint(p_translated);

    qreal newPan = m_currentLocation.pan() + translatedVector.pan();
    qreal newTilt = m_currentLocation.tilt() + translatedVector.tilt();
    qDebug() << "TARGET: Pan: " << newPan << "Tilt: " << newTilt;

    setPan(newPan);
    const QString panCmd = QString("/eos/user/1/chan/%1/param/pan=%2").arg(m_channel).arg(newPan);
    m_manager->sendMessage(panCmd);

    const QString tiltCmd = QString("/eos/user/1/chan/%1/param/tilt=%2").arg(m_channel).arg(newTilt);
    m_manager->sendMessage(tiltCmd);
    setTilt(newTilt);


    const QString resetCmd = QString("/eos/user/1/cmd");
    const QString cmd = "Chan 1#";
    m_manager->sendMessage(resetCmd, cmd);
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

void
DemoOutput::onMessageRecieved(OSCMessage message)
{
    if(message.pathStartsWith("/eos/out/pantilt"))
    {
        // This message has six arguements:
        // Pan min, Pan max, tilt min, tilt max, current pan, current tilt.
        // For now, we need to assume that the channel we're dealing with is active.
        qDebug() << "MESSAGE RECIEVED: ";
        qDebug() << "Old Current: P: " << m_currentLocation.pan() << " T: " << m_currentLocation.tilt();
        const QVector<QVariant>& arguments = message.arguments();
        qDebug() << arguments;
        if(arguments.size()>4) {
            m_currentLocation.setMinPan(arguments[0].toFloat());
            m_currentLocation.setMaxPan(arguments[1].toFloat());
            m_currentLocation.setMinTilt(arguments[2].toFloat());
            m_currentLocation.setMaxTilt(arguments[3].toFloat());
            m_currentLocation.setPan(arguments[4].toFloat());
            m_currentLocation.setTilt(arguments[5].toFloat());
            setPan(m_currentLocation.pan());
            setTilt(m_currentLocation.tilt());
        }

        qDebug() << "New Current: P: "  << m_currentLocation.pan() << " T: " << m_currentLocation.tilt();;

    }

}
