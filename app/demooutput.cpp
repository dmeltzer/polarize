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
    , m_manager(0)
{
    m_manager = new OSCNetworkManager;
    m_manager->setIpAddress(QHostAddress("127.0.0.1"));
    m_manager->setUseTcp(true);
    m_manager->setEnabled(true);
}

void
DemoOutput::output(const QStringList &source, const QStringList &target)
{
    qDebug() << "TRIGERED: " << source << " TARGET: " << target;
    QVector3D sourcePoint(source[0].toFloat(), source[1].toFloat(), source[2].toFloat());
    QVector3D targetPoint(target[0].toFloat(), target[1].toFloat(), target[2].toFloat());

    QVector3D calculatedVector = targetPoint - sourcePoint;

    PolarPoint dest(calculatedVector);
    setPan(dest.pan());
    const QString panCmd = QString("/eos/user/0/chan/1/param/pan=%1").arg(dest.pan());
    m_manager->sendMessage(panCmd);

    const QString tiltCmd = QString("/eos/user/0/chan/1/param/tilt=%1").arg(dest.tilt());
    m_manager->sendMessage(tiltCmd);
    setTilt(dest.tilt());
    qDebug() << "Pan: " << dest.pan() << "Tilt: " << dest.tilt();
}
