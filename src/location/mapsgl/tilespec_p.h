/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef TILESPEC_P_H
#define TILESPEC_P_H

#include <QString>

QT_BEGIN_NAMESPACE

class TileSpecPrivate
{
public:
    TileSpecPrivate();
    TileSpecPrivate(const TileSpecPrivate &other);
    TileSpecPrivate(const QString &plugin, int mapId, int zoom, int x, int y);
    ~TileSpecPrivate();

    TileSpecPrivate& operator = (const TileSpecPrivate &other);

    bool operator == (const TileSpecPrivate &rhs) const;
    bool operator < (const TileSpecPrivate &rhs) const;

    QString plugin_;
    int mapId_;
    int zoom_;
    int x_;
    int y_;
};

QT_END_NAMESPACE

#endif // TILESPEC_P_H