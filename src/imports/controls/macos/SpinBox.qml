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

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Templates 2.12 as T
import QtQuick.NativeStyle 6.0 as NativeStyle

T.SpinBox {
    id: control

    property bool nativeBackground: background instanceof NativeStyle.StyleItem
    property bool nativeIndicators: true

    Component.onCompleted: {
        // Work-around: up.indicator will not emit changed, so we
        // need to evaluate nativeIndicators after completed instead.
        nativeIndicators = up.indicator.hasOwnProperty("_qt_default")
                && down.indicator.hasOwnProperty("_qt_default")
    }

    implicitWidth: implicitBackgroundWidth + leftInset + rightInset
    implicitHeight: Math.max(implicitBackgroundHeight, up.implicitIndicatorHeight + down.implicitIndicatorHeight)
                    + topInset + bottomInset

    spacing: 2

    // Push the background right to make room for the indicators
    rightInset: nativeIndicators ? up.implicitIndicatorWidth + spacing : 0

    leftPadding: nativeBackground ? background.contentPadding.left: 0
    topPadding: nativeBackground ? background.contentPadding.top: 0
    rightPadding: (nativeBackground ? background.contentPadding.right : 0) + rightInset
    bottomPadding: nativeBackground ? background.contentPadding.bottom: 0

    validator: IntValidator {
        locale: control.locale.name
        bottom: Math.min(control.from, control.to)
        top: Math.max(control.from, control.to)
    }

    contentItem: TextInput {
        text: control.displayText
        font: control.font
        color: control.palette.text
        selectionColor: control.palette.highlight
        selectedTextColor: control.palette.highlightedText
        horizontalAlignment: Qt.AlignLeft
        verticalAlignment: Qt.AlignVCenter

        topPadding: 2
        bottomPadding: 2
        leftPadding: 10
        rightPadding: 10

        readOnly: !control.editable
        validator: control.validator
        inputMethodHints: control.inputMethodHints
    }

    NativeStyle.SpinBox {
        id: upAndDown
        control: control
        subControl: NativeStyle.SpinBox.Up
        visible: nativeIndicators
        x: up.indicator.x
        y: up.indicator.y
        useNinePatchImage: false
    }

    up.indicator: Item {
        x: parent.width - width
        y: (parent.height / 2) - height
        implicitWidth: upAndDown.width
        implicitHeight: upAndDown.height / 2
        property bool _qt_default
    }

    down.indicator: Item {
        x: parent.width - width
        y: up.indicator.y + upAndDown.height / 2
        implicitWidth: upAndDown.width
        implicitHeight: upAndDown.height / 2
        property bool _qt_default
    }

    background: NativeStyle.SpinBox {
        control: control
        subControl: NativeStyle.SpinBox.Frame
        contentWidth: contentItem.implicitWidth
        contentHeight: contentItem.implicitHeight
    }
}
