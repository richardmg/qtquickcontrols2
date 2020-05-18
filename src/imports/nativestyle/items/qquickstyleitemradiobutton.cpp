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

#include "qquickstyleitemradiobutton.h"

void QQuickStyleItemRadioButton::connectToControl()
{
    QQuickStyleItem::connectToControl();
    auto checkbox = control<QQuickRadioButton>();
    connect(checkbox, &QQuickRadioButton::downChanged, this, &QQuickStyleItem::markImageDirty);
    connect(checkbox, &QQuickRadioButton::checkedChanged, this, &QQuickStyleItem::markImageDirty);
}

ControlGeometry QQuickStyleItemRadioButton::calculateControlGeometry()
{
    QStyleOptionButton styleOption;
    initStyleOption(styleOption);
    ControlGeometry cg;

    cg.minimumSize = style()->sizeFromContents(QStyle::CT_RadioButton, &styleOption, QSize(0, 0));
    cg.implicitSize = cg.minimumSize;
    styleOption.rect = QRect(QPoint(0, 0), cg.implicitSize);
    cg.contentRect = style()->subElementRect(QStyle::SE_RadioButtonContents, &styleOption);
    cg.layoutRect = style()->subElementRect(QStyle::SE_RadioButtonLayoutItem, &styleOption);

    return cg;
}

void QQuickStyleItemRadioButton::paintEvent(QPainter *painter)
{
    QStyleOptionButton styleOption;
    initStyleOption(styleOption);
    style()->drawControl(QStyle::CE_RadioButton, &styleOption, painter);
}

void QQuickStyleItemRadioButton::initStyleOption(QStyleOptionButton &styleOption)
{
    initStyleOptionBase(styleOption);
    auto checkbox = control<QQuickRadioButton>();

    styleOption.state |= checkbox->isDown() ? QStyle::State_Sunken : QStyle::State_Raised;
    styleOption.state |= checkbox->isChecked() ? QStyle::State_On : QStyle::State_Off;
}
