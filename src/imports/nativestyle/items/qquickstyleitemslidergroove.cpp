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

#include "qquickstyleitemslidergroove.h"

void QQuickStyleItemSliderGroove::connectToControl()
{
    QQuickStyleItem::connectToControl();
    auto slider = control<QQuickSlider>();
    connect(slider, &QQuickSlider::fromChanged, this, &QQuickStyleItem::markImageDirty);
    connect(slider, &QQuickSlider::toChanged, this, &QQuickStyleItem::markImageDirty);
    connect(slider, &QQuickSlider::positionChanged, this, &QQuickStyleItem::markImageDirty);
    connect(slider, &QQuickSlider::valueChanged, this, &QQuickStyleItem::markImageDirty);
    connect(slider, &QQuickSlider::stepSizeChanged, this, &QQuickStyleItem::markImageDirty);
    connect(slider, &QQuickSlider::pressedChanged, this, &QQuickStyleItem::markImageDirty);
    connect(slider, &QQuickSlider::orientationChanged, this, &QQuickStyleItem::markImageDirty);
}

ControlGeometry QQuickStyleItemSliderGroove::calculateControlGeometry()
{
    QStyleOptionSlider styleOption;
    initStyleOption(styleOption);

    ControlGeometry cg;
    cg.implicitSize = style()->sizeFromContents(QStyle::CT_Slider, &styleOption, QSize());
    styleOption.rect.setSize(cg.implicitSize);
    cg.minimumSize = style()->subControlRect(QStyle::CC_Slider, &styleOption, QStyle::SC_SliderGroove).size();

    return cg;
}

void QQuickStyleItemSliderGroove::paintEvent(QPainter *painter)
{
    QStyleOptionSlider styleOption;
    initStyleOption(styleOption);
    style()->drawComplexControl(QStyle::CC_Slider, &styleOption, painter);
}

void QQuickStyleItemSliderGroove::initStyleOption(QStyleOptionSlider &styleOption)
{
    initStyleOptionBase(styleOption);
    auto slider = control<QQuickSlider>();

    styleOption.subControls = QStyle::SC_SliderGroove;
    styleOption.activeSubControls = QStyle::SC_None;
    styleOption.orientation = slider->orientation();
    styleOption.tickInterval = slider->stepSize();

    if (slider->isPressed())
        styleOption.state |= QStyle::State_Sunken;

    if (slider->stepSize() == 0) {
        styleOption.minimum = 0;
        styleOption.maximum = 10000;
        styleOption.sliderPosition = slider->position() * styleOption.maximum;
    } else {
        styleOption.minimum = slider->from();
        styleOption.maximum = slider->to();
        styleOption.sliderPosition = slider->value();

        // TODO: add proper API for tickmarks
        const int index = slider->metaObject()->indexOfProperty("qqc2_style_tickPosition");
        if (index != -1) {
            const int tickPosition = slider->metaObject()->property(index).read(slider).toInt();
            styleOption.tickPosition = QStyleOptionSlider::TickPosition(tickPosition);
            if (styleOption.tickPosition != QStyleOptionSlider::NoTicks)
                styleOption.subControls |= QStyle::SC_SliderTickmarks;
        }
    }
}
