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

#ifndef QDECLARATIVESUPPORTEDCATEGORIESMODEL_H
#define QDECLARATIVESUPPORTEDCATEGORIESMODEL_H

#include <qdeclarativegeoserviceprovider_p.h>

#include <QObject>
#include <QtCore/QStringList>
#include <QAbstractListModel>
#include <QDeclarativeListProperty>

#include <QtLocation/QPlaceCategory>

#include "qdeclarativecategory_p.h"

QT_BEGIN_NAMESPACE

class QGeoServiceProvider;
class QPlaceManager;
class QPlaceReply;

class PlaceCategoryNode
{
public:
    QString parentId;
    QStringList childIds;
    QSharedPointer<QDeclarativeCategory> declCategory;
};

class QDeclarativeSupportedCategoriesModel : public QAbstractItemModel, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_ENUMS(Status)

    Q_PROPERTY(QDeclarativeGeoServiceProvider *plugin READ plugin WRITE setPlugin NOTIFY pluginChanged)
    Q_PROPERTY(bool hierarchical READ hierarchical WRITE setHierarchical NOTIFY hierarchicalChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged);

    Q_INTERFACES(QDeclarativeParserStatus)
    Q_ENUMS(Roles)

public:
    explicit QDeclarativeSupportedCategoriesModel(QObject *parent = 0);
    virtual ~QDeclarativeSupportedCategoriesModel();

    // From QDeclarativeParserStatus
    virtual void classBegin() {}
    virtual void componentComplete();

    // From QAbstractItemModel
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;

    enum Roles {
        CategoryRole = Qt::UserRole
    };

    enum Status {Ready, Updating, Error};

    void setPlugin(QDeclarativeGeoServiceProvider *plugin);
    QDeclarativeGeoServiceProvider* plugin() const;

    void setHierarchical(bool hierarchical);
    bool hierarchical() const;

    Q_INVOKABLE void update();
    Q_INVOKABLE QString errorString() const;

    Status status() const;
    void setStatus(Status status);

signals:
    void pluginChanged();
    void hierarchicalChanged();
    void statusChanged();

private slots:
    void replyFinished();
    void addedCategory(const QPlaceCategory &category, const QString &parentId);
    void updatedCategory(const QPlaceCategory &category, const QString &parentId);
    void removedCategory(const QString &categoryId, const QString &parentId);
    void connectNotificationSignals();
    void updateCategories();

private:
    QStringList populateCategories(QPlaceManager *, const QPlaceCategory &parent);
    QModelIndex index(const QString &categoryId) const;
    int rowToAddChild(PlaceCategoryNode *, const QPlaceCategory &category);

    QPlaceManager *manager(bool stateCheck = true);

    QPlaceReply *m_response;

    QDeclarativeGeoServiceProvider *m_plugin;
    bool m_hierarchical;
    bool m_complete;
    Status m_status;
    QString m_errorString;

    QHash<QString, PlaceCategoryNode *> m_categoriesTree;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QT_PREPEND_NAMESPACE(QDeclarativeSupportedCategoriesModel));

#endif // QDECLARATIVESUPPORTEDCATEGORIESMODEL_H
