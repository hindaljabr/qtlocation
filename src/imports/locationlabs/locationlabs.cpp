/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

//#include <QtLocationLabs/private/qmapiconobject_p.h>
//#include <QtLocationLabs/private/qmapobjectview_p.h>
#include <QtLocationLabs/private/qmaprouteobject_p.h>
//#include <QtLocationLabs/private/qdeclarativenavigator_p.h>

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>
#include <QtCore/QDebug>

static void initResources()
{
#ifdef QT_STATIC
    Q_INIT_RESOURCE(qmake_QtLocationLabs);
#endif
}

QT_BEGIN_NAMESPACE


class QtLocationLabsDeclarativeModule: public QQmlExtensionPlugin
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid
                      FILE "plugin.json")

public:
    QtLocationLabsDeclarativeModule(QObject *parent = 0) : QQmlExtensionPlugin(parent) { initResources(); }
    virtual void registerTypes(const char *uri)
    {
        if (QLatin1String(uri) == QLatin1String("Qt.labs.location")) {

            // @uri QtLocationLabs
            int major = 5;
            int minor = 11;

            // Register the 5.11 types
//            qmlRegisterType<QDeclarativeNavigator>(uri, major, minor, "Navigator");
//            qmlRegisterType<QMapIconObject>(uri, major, minor, "MapIconObject");
//            qmlRegisterType<QMapObjectView>(uri, major, minor, "MapObjectView");
            qmlRegisterType<QMapRouteObject>(uri, major, minor, "MapRouteObject");

            // Register the latest Qt version as QML type version
            qmlRegisterModule(uri, QT_VERSION_MAJOR, QT_VERSION_MINOR);
        } else {
            qDebug() << "Unsupported URI given to load location QML plugin: " << QLatin1String(uri);
        }
    }
};

#include "locationlabs.moc"

QT_END_NAMESPACE