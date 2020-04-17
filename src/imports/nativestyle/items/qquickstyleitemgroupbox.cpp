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

#include "qquickstyleitemgroupbox.h"

ControlGeometry QQuickStyleItemGroupBox::calculateControlGeometry()
{
    QStyleOptionGroupBox styleOption;
    initStyleOption(styleOption);

    ControlGeometry cg;
    cg.imageSize = style()->sizeFromContents(QStyle::CT_GroupBox, &styleOption, QSize());

    if (!control<QQuickGroupBox>()->title().isEmpty()) {
        // We don't draw the title, but we need to take
        // it into calculation for the control size
        styleOption.text = QStringLiteral(" ");
        styleOption.subControls |= QStyle::SC_GroupBoxLabel;
    }

    cg.controlSize = style()->sizeFromContents(QStyle::CT_GroupBox, &styleOption, contentSize());
    styleOption.rect.setSize(cg.controlSize);
    cg.contentRect = style()->subControlRect(QStyle::CC_GroupBox, &styleOption, QStyle::SC_GroupBoxContents);
    cg.backgroundRect = style()->subControlRect(QStyle::CC_GroupBox, &styleOption, QStyle::SC_GroupBoxFrame);
    return cg;
}

void QQuickStyleItemGroupBox::paintEvent(QPainter *painter)
{
    QStyleOptionGroupBox styleOption;
    initStyleOption(styleOption);
    style()->drawComplexControl(QStyle::CC_GroupBox, &styleOption, painter);
}

void QQuickStyleItemGroupBox::initStyleOption(QStyleOptionGroupBox &styleOption)
{
    initStyleOptionBase(styleOption);
    styleOption.subControls = QStyle::SC_GroupBoxFrame;
    styleOption.lineWidth = 1;
}
