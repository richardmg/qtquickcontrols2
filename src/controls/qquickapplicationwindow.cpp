/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
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

#include "qquickapplicationwindow_p.h"

#include <QtQuick/private/qquickitem_p.h>
#include <QtQuick/private/qquickitemchangelistener_p.h>

QT_BEGIN_NAMESPACE

/*!
    \qmltype ApplicationWindow
    \inherits Window
    \instantiates QQuickApplicationWindow
    \inqmlmodule QtQuick.Controls
    \ingroup application
    \brief An application window.

    TODO
*/

class QQuickApplicationWindowPrivate : public QQuickItemChangeListener
{
    Q_DECLARE_PUBLIC(QQuickApplicationWindow)

public:
    QQuickApplicationWindowPrivate() : contentWidth(0), contentHeight(0), header(Q_NULLPTR), footer(Q_NULLPTR) { }

    void relayout();

    void itemImplicitWidthChanged(QQuickItem *item) Q_DECL_OVERRIDE;
    void itemImplicitHeightChanged(QQuickItem *item) Q_DECL_OVERRIDE;

    qreal contentWidth;
    qreal contentHeight;
    QQuickItem *header;
    QQuickItem *footer;
    QQuickApplicationWindow *q_ptr;
};

void QQuickApplicationWindowPrivate::relayout()
{
    Q_Q(QQuickApplicationWindow);
    QQuickItem *content = q->contentItem();
    qreal hh = header ? header->height() : 0;
    qreal fh = footer ? footer->height() : 0;

    content->setY(hh);
    content->setHeight(q->height() - hh - fh);

    if (header)
        header->setY(-hh);
    if (footer)
        footer->setY(content->height());
}

void QQuickApplicationWindowPrivate::itemImplicitWidthChanged(QQuickItem *item)
{
    Q_UNUSED(item);
    relayout();
}

void QQuickApplicationWindowPrivate::itemImplicitHeightChanged(QQuickItem *item)
{
    Q_UNUSED(item);
    relayout();
}

QQuickApplicationWindow::QQuickApplicationWindow(QWindow *parent) :
    QQuickWindowQmlImpl(parent), d_ptr(new QQuickApplicationWindowPrivate)
{
    d_ptr->q_ptr = this;
}

QQuickApplicationWindow::~QQuickApplicationWindow()
{
    Q_D(QQuickApplicationWindow);
    if (d->header)
        QQuickItemPrivate::get(d->header)->removeItemChangeListener(d, QQuickItemPrivate::ImplicitWidth | QQuickItemPrivate::ImplicitHeight);
    if (d->footer)
        QQuickItemPrivate::get(d->footer)->removeItemChangeListener(d, QQuickItemPrivate::ImplicitWidth | QQuickItemPrivate::ImplicitHeight);
}

/*!
    \qmlproperty Item QtQuickControls2::ApplicationWindow::header

    TODO
*/
QQuickItem *QQuickApplicationWindow::header() const
{
    Q_D(const QQuickApplicationWindow);
    return d->header;
}

void QQuickApplicationWindow::setHeader(QQuickItem *header)
{
    Q_D(QQuickApplicationWindow);
    if (d->header != header) {
        delete d->header;
        d->header = header;
        if (header) {
            header->setParentItem(contentItem());
            QQuickItemPrivate *p = QQuickItemPrivate::get(header);
            p->addItemChangeListener(d, QQuickItemPrivate::ImplicitWidth | QQuickItemPrivate::ImplicitHeight);
            if (qFuzzyIsNull(header->z()))
                header->setZ(1);
        }
        emit headerChanged();
    }
}

/*!
    \qmlproperty Item QtQuickControls2::ApplicationWindow::footer

    TODO
*/
QQuickItem *QQuickApplicationWindow::footer() const
{
    Q_D(const QQuickApplicationWindow);
    return d->footer;
}

void QQuickApplicationWindow::setFooter(QQuickItem *footer)
{
    Q_D(QQuickApplicationWindow);
    if (d->footer != footer) {
        delete d->footer;
        d->footer = footer;
        if (footer) {
            footer->setParentItem(contentItem());
            QQuickItemPrivate *p = QQuickItemPrivate::get(footer);
            p->addItemChangeListener(d, QQuickItemPrivate::ImplicitWidth | QQuickItemPrivate::ImplicitHeight);
            if (qFuzzyIsNull(footer->z()))
                footer->setZ(1);
        }
        emit footerChanged();
    }
}

/*!
    \qmlproperty real QtQuickControls2::ApplicationWindow::contentWidth

    TODO
*/
qreal QQuickApplicationWindow::contentWidth() const
{
    Q_D(const QQuickApplicationWindow);
    return d->contentWidth;
}

void QQuickApplicationWindow::setContentWidth(qreal width)
{
    Q_D(QQuickApplicationWindow);
    if (d->contentWidth != width) {
        d->contentWidth = width;
        emit contentWidthChanged();
    }
}

/*!
    \qmlproperty real QtQuickControls2::ApplicationWindow::contentHeight

    TODO
*/
qreal QQuickApplicationWindow::contentHeight() const
{
    Q_D(const QQuickApplicationWindow);
    return d->contentHeight;
}

void QQuickApplicationWindow::setContentHeight(qreal height)
{
    Q_D(QQuickApplicationWindow);
    if (d->contentHeight != height) {
        d->contentHeight = height;
        emit contentHeightChanged();
    }
}

void QQuickApplicationWindow::resizeEvent(QResizeEvent *event)
{
    QQuickWindowQmlImpl::resizeEvent(event);

    Q_D(QQuickApplicationWindow);
    if (d->header) {
        QQuickItemPrivate *p = QQuickItemPrivate::get(d->header);
        if (!p->widthValid) {
            d->header->setWidth(width());
            p->widthValid = false;
        }
    }
    if (d->footer) {
        QQuickItemPrivate *p = QQuickItemPrivate::get(d->footer);
        if (!p->widthValid) {
            d->footer->setWidth(width());
            p->widthValid = false;
        }
    }
    d->relayout();
}

QT_END_NAMESPACE