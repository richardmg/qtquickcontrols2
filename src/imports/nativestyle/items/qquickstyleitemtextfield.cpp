/****************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
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

#include "qquickstyleitemtextfield.h"

void QQuickStyleItemTextField::connectToControl()
{
    QQuickStyleItem::connectToControl();
    auto textField = control<QQuickTextField>();
    connect(textField, &QQuickTextField::readOnlyChanged, this, &QQuickStyleItem::markImageDirty);
    connect(textField, &QQuickTextField::focusChanged, this, &QQuickStyleItem::markImageDirty);
}

ControlGeometry QQuickStyleItemTextField::calculateControlGeometry()
{
    QStyleOptionFrame styleOption;
    initStyleOption(styleOption);
    ControlGeometry cg;

    cg.minimumSize = style()->sizeFromContents(QStyle::CT_LineEdit, &styleOption, QSize(0, 0));
    cg.implicitSize = style()->sizeFromContents(QStyle::CT_LineEdit, &styleOption, contentSize());
    styleOption.rect = QRect(QPoint(0, 0), cg.implicitSize);
    cg.contentRect = style()->subElementRect(QStyle::SE_LineEditContents, &styleOption);

    return cg;
}

void QQuickStyleItemTextField::paintEvent(QPainter *painter)
{
    QStyleOptionFrame styleOption;
    initStyleOption(styleOption);
    style()->drawPrimitive(QStyle::PE_PanelLineEdit, &styleOption, painter);
}

void QQuickStyleItemTextField::initStyleOption(QStyleOptionFrame &styleOption)
{
    initStyleOptionBase(styleOption);
    auto textField = control<QQuickTextField>();

    styleOption.lineWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, &styleOption);
    styleOption.midLineWidth = 0;
    styleOption.state |= QStyle::State_Sunken;
    if (textField->isReadOnly())
        styleOption.state |= QStyle::State_ReadOnly;
}
