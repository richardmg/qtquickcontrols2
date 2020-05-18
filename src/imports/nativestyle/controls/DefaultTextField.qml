/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
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

T.TextField {
    id: control

    property bool nativeBackground: background instanceof NativeStyle.StyleItem

    implicitWidth: Math.max(96, background.implicitWidth + leftPadding + rightPadding + leftInset + rightInset)
    implicitHeight: background.implicitHeight + topPadding + bottomPadding + topInset + bottomInset

    font.pixelSize: nativeBackground ? background.styleFont(control).pixelSize : undefined

    leftPadding: nativeBackground ? background.contentPadding.left: 7
    rightPadding: nativeBackground ? background.contentPadding.right: 7
    topPadding: nativeBackground ? background.contentPadding.top: 3
    bottomPadding: nativeBackground ? background.contentPadding.bottom: 3

    topInset: nativeBackground ? background.insets.top : 0
    bottomInset: nativeBackground ? background.insets.bottom : 0
    leftInset: nativeBackground ? background.insets.left : 0
    rightInset: nativeBackground ? background.insets.right : 0

    color: control.palette.text
    selectionColor: control.palette.highlight
    selectedTextColor: control.palette.highlightedText
    placeholderTextColor: Color.transparent(control.color, 0.5)
    verticalAlignment: TextInput.AlignTop

    PlaceholderText {
        id: placeholder
        height: control.height
        topPadding: control.topPadding
        bottomPadding: control.bottomPadding
        leftPadding: control.leftPadding
        rightPadding: control.rightPadding
        text: control.placeholderText
        font: control.font
        color: control.placeholderTextColor
        verticalAlignment: control.verticalAlignment
        visible: !control.length && !control.preeditText && (!control.activeFocus || control.horizontalAlignment !== Qt.AlignHCenter)
        elide: Text.ElideRight
        renderType: control.renderType
    }

    background: NativeStyle.TextField {
        control: control
        contentWidth: Math.max(control.contentWidth, placeholder.implicitWidth)
        contentHeight: control.contentHeight
    }
}
