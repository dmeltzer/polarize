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

#ifndef DEMOOUTPUT_H
#define DEMOOUTPUT_H

#include <QObject>
#include <QDebug>
#include <QJSValue>
#include "src/polarpoint.h"
#include "src/etc-osc/OSCNetworkManager.h"
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
    OSCNetworkManager *m_manager;
};

#endif // DEMOOUTPUT_H
