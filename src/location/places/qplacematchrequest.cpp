/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qplacematchrequest.h"

#include <QtCore/QSharedData>
#include <QtCore/QList>

QT_BEGIN_NAMESPACE

class QPlaceMatchRequestPrivate : public QSharedData
{
public:
    QPlaceMatchRequestPrivate();
    QPlaceMatchRequestPrivate(const QPlaceMatchRequestPrivate &other);
    ~QPlaceMatchRequestPrivate();

    QPlaceMatchRequestPrivate &operator=(const QPlaceMatchRequestPrivate &other);
    bool operator==(const QPlaceMatchRequestPrivate &other) const;

    void clear();

    QList<QPlace> places;
    QVariantMap parameters;
};

QPlaceMatchRequestPrivate::QPlaceMatchRequestPrivate()
    :   QSharedData()
{
}

QPlaceMatchRequestPrivate::QPlaceMatchRequestPrivate(const QPlaceMatchRequestPrivate &other)
    : QSharedData(other),
      places(other.places),
      parameters(other.parameters)
{
}

QPlaceMatchRequestPrivate::~QPlaceMatchRequestPrivate()
{
}

QPlaceMatchRequestPrivate &QPlaceMatchRequestPrivate::operator=(const QPlaceMatchRequestPrivate &other)
{
    if (this != &other) {
        places = other.places;
        parameters = other.parameters;
    }

    return *this;
}

bool QPlaceMatchRequestPrivate::operator==(const QPlaceMatchRequestPrivate &other) const
{
    return (places == other.places
            && parameters == other.parameters);
}

void QPlaceMatchRequestPrivate::clear()
{
    places.clear();
    parameters.clear();
}

/*!
    \class QPlaceMatchRequest
    \inmodule QtLocation
    \ingroup QtLocation-places
    \ingroup QtLocation-places-requests
    \since QtLocation 5.0

    \brief The QPlaceMatchRequest class is used to find places from one manager that match those from another.  It represents
    a set of request parameters.

    Places from another manager that may have corresponding/matching places in the current manager are assigned using setPlaces() or setResults().
    A set of further parameters are specified which determines the criteria for matching.

    The typical key for matching is the QPlaceMatchRequest::AlternativeId, the value is an alternative id attribute type of the format
    x_id_<provider name> eg x_id_nokia.  The provider name is name supplied to the QGeoServiceProvider instance.

    See \l {Matching places between managers} for an example on how to use a match request.

    \sa QPlaceMatchReply, QPlaceManager
*/

/*!
   \variable QPlaceMatchRequest::AlternativeId
   The key to specify that matching is to be accomplished via an alternative place id.
*/
const QString QPlaceMatchRequest::AlternativeId(QLatin1String("alternativeId"));

/*!
    Default constructor. Constructs a new request object.
*/
QPlaceMatchRequest::QPlaceMatchRequest()
    : d_ptr(new QPlaceMatchRequestPrivate())
{
}

/*!
    Constructs a copy of \a other.
*/
QPlaceMatchRequest::QPlaceMatchRequest(const QPlaceMatchRequest &other)
    : d_ptr(other.d_ptr)
{
}

/*!
    Destroys the request object.
*/
QPlaceMatchRequest::~QPlaceMatchRequest()
{
}

/*!
    Assigns \a other to this search request and returns a reference
    to this match request.
*/
QPlaceMatchRequest &QPlaceMatchRequest::operator= (const QPlaceMatchRequest & other)
{
    d_ptr = other.d_ptr;
    return *this;
}

/*!
    Returns true if \a other is equal to this match request,
    otherwise returns false.
*/
bool QPlaceMatchRequest::operator== (const QPlaceMatchRequest &other) const
{
    Q_D(const QPlaceMatchRequest);
    return *d == *other.d_func();
}

/*!
    Returns true if \a other is not equal to this match request,
    otherwise returns false.
*/
bool QPlaceMatchRequest::operator!= (const QPlaceMatchRequest &other) const
{
    Q_D(const QPlaceMatchRequest);
    return !(*d == *other.d_func());
}


/*!
    Returns a list of places which are to be matched.
*/
QList<QPlace> QPlaceMatchRequest::places() const
{
    Q_D(const QPlaceMatchRequest);
    return d->places;
}

/*!
    Sets a list of \a places which are to be matched.

    \sa setResults()
*/
void QPlaceMatchRequest::setPlaces(const QList<QPlace> places)
{
    Q_D(QPlaceMatchRequest);
    d->places = places;
}

/*!
    Convenience function which uses a set of search \a results to set
    the places which should be matched.

    \sa setPlaces()
*/
void QPlaceMatchRequest::setResults(const QList<QPlaceSearchResult> &results)
{
    Q_D(QPlaceMatchRequest);
    QList<QPlace> places;
    foreach (const QPlaceSearchResult &result, results)
        places.append(result.place());

    d->places = places;
}

/*!
    Returns the paramaters for matching places.
*/
QVariantMap QPlaceMatchRequest::parameters() const
{
    Q_D(const QPlaceMatchRequest);
    return d->parameters;
}

/*!
    Sets the \a parameters for matching places.
*/
void QPlaceMatchRequest::setParameters(const QVariantMap &parameters)
{
    Q_D(QPlaceMatchRequest);
    d->parameters = parameters;
}

/*!
    Clears the match request.
*/
void QPlaceMatchRequest::clear()
{
    Q_D(QPlaceMatchRequest);
    d->clear();
}

inline QPlaceMatchRequestPrivate* QPlaceMatchRequest::d_func()
{
    return static_cast<QPlaceMatchRequestPrivate *>(d_ptr.data());
}

inline const QPlaceMatchRequestPrivate* QPlaceMatchRequest::d_func() const
{
    return static_cast<const QPlaceMatchRequestPrivate *>(d_ptr.constData());
}

QT_END_NAMESPACE
