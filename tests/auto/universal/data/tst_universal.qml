/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.2
import QtQuick.Window 2.2
import QtTest 1.0
import Qt.labs.controls 1.0
import Qt.labs.controls.universal 1.0

TestCase {
    id: testCase
    width: 200
    height: 200
    visible: true
    when: windowShown
    name: "Universal"

    Component {
        id: button
        Button { }
    }

    Component {
        id: styledButton
        Button {
            Universal.theme: Universal.Dark
            Universal.accent: Universal.Violet
        }
    }

    Component {
        id: window
        Window { }
    }

    Component {
        id: styledWindow
        Window {
            Universal.theme: Universal.Dark
            Universal.accent: Universal.Green
        }
    }

    Component {
        id: loader
        Loader {
            active: false
            sourceComponent: Button { }
        }
    }

    Component {
        id: swipeView
        SwipeView {
            Universal.theme: Universal.Dark
            Button { }
        }
    }

    Component {
        id: menu
        Item {
            Universal.accent: Universal.Red
            property alias menu: popup
            Menu {
                id: popup
                Universal.theme: Universal.Dark
                MenuItem { }
            }
        }
    }

    function test_defaults() {
        var control = button.createObject(testCase)
        verify(control)
        verify(control.Universal)
        compare(control.Universal.accent, "#3e65ff") // Universal.Cobalt
        compare(control.Universal.theme, Universal.Light)
        control.destroy()
    }

    function test_set() {
        var control = button.createObject(testCase)
        verify(control)
        control.Universal.accent = Universal.Steel
        control.Universal.theme = Universal.Dark
        compare(control.Universal.accent, "#647687") // Universal.Steel
        compare(control.Universal.theme, Universal.Dark)
        control.destroy()
    }

    function test_reset() {
        var control = styledButton.createObject(testCase)
        verify(control)
        compare(control.Universal.accent, "#aa00ff") // Universal.Violet
        compare(control.Universal.theme, Universal.Dark)
        control.Universal.accent = undefined
        control.Universal.theme = undefined
        compare(control.Universal.accent, testCase.Universal.accent)
        compare(control.Universal.theme, testCase.Universal.theme)
        control.destroy()
    }

    function test_inheritance_data() {
        return [
            { tag: "accent", value1: "#a20025" /*Universal.Crimson*/, value2: "#6a00ff" /*Universal.Indigo*/ },
            { tag: "theme", value1: Universal.Dark, value2: Universal.Light },
        ]
    }

    function test_inheritance(data) {
        var prop = data.tag
        var parent = button.createObject(testCase)
        parent.Universal[prop] = data.value1
        compare(parent.Universal[prop], data.value1)

        var child1 = button.createObject(parent)
        compare(child1.Universal[prop], data.value1)

        parent.Universal[prop] = data.value2
        compare(parent.Universal[prop], data.value2)
        compare(child1.Universal[prop], data.value2)

        var child2 = button.createObject(parent)
        compare(child2.Universal[prop], data.value2)

        child2.Universal[prop] = data.value1
        compare(child2.Universal[prop], data.value1)
        compare(child1.Universal[prop], data.value2)
        compare(parent.Universal[prop], data.value2)

        parent.Universal[prop] = undefined
        verify(parent.Universal[prop] !== data.value1)
        verify(parent.Universal[prop] !== undefined)
        compare(child1.Universal[prop], parent.Universal[prop])
        verify(child2.Universal[prop] !== parent.Universal[prop])

        var grandChild1 = button.createObject(child1)
        var grandChild2 = button.createObject(child2)
        compare(grandChild1.Universal[prop], child1.Universal[prop])
        compare(grandChild2.Universal[prop], child2.Universal[prop])

        var themelessGrandGrandChild = button.createObject(grandChild1)
        var grandGrandGrandChild1 = button.createObject(themelessGrandGrandChild)
        compare(grandGrandGrandChild1.Universal[prop], parent.Universal[prop])

        child1.Universal[prop] = data.value2
        compare(child1.Universal[prop], data.value2)
        compare(grandChild1.Universal[prop], data.value2)
        compare(grandGrandGrandChild1.Universal[prop], data.value2)

        parent.destroy()
    }

    function test_window() {
        var parent = window.createObject()

        var control = button.createObject(parent.contentItem)
        compare(control.Universal.accent, parent.Universal.accent)
        compare(control.Universal.theme, parent.Universal.theme)

        var styledChild = styledWindow.createObject(window)
        verify(styledChild.Universal.accent !== parent.Universal.accent)
        verify(styledChild.Universal.theme !== parent.Universal.theme)

        var unstyledChild = window.createObject(window)
        compare(unstyledChild.Universal.accent, parent.Universal.accent)
        compare(unstyledChild.Universal.theme, parent.Universal.theme)

        parent.Universal.accent = Universal.Cyan
        compare(control.Universal.accent, "#1ba1e2") // Universal.Cyan
        verify(styledChild.Universal.accent !== Universal.Cyan)
        // ### TODO: compare(unstyledChild.Universal.accent, Universal.Cyan)

        parent.destroy()
    }

    function test_loader() {
        var control = loader.createObject(testCase)
        control.Universal.accent = Universal.Lime
        control.active = true
        compare(control.item.Universal.accent, "#a4c400") // Universal.Lime
        control.Universal.accent = Universal.Pink
        compare(control.item.Universal.accent, "#f472d0") // Universal.Pink
        control.active = false
        control.Universal.accent = Universal.Brown
        control.active = true
        compare(control.item.Universal.accent, "#825a2c") // Universal.Brown
        control.destroy()
    }

    function test_swipeView() {
        var control = swipeView.createObject(testCase)
        verify(control)
        var child = control.itemAt(0)
        verify(child)
        compare(control.Universal.theme, Universal.Dark)
        compare(child.Universal.theme, Universal.Dark)
        control.destroy()
    }

    function test_menu() {
        var container = menu.createObject(testCase)
        verify(container)
        verify(container.menu)
        var child = container.menu.itemAt(0)
        verify(child)
        compare(container.Universal.theme, Universal.Light)
        compare(container.menu.Universal.theme, Universal.Dark)
        compare(child.Universal.theme, Universal.Dark)
        compare(container.Universal.accent, "#e51400") // Red
        compare(container.menu.Universal.accent, "#e51400") // Red
        compare(child.Universal.accent, "#e51400") // Red
        container.destroy()
    }

    function test_colors() {
        var control = button.createObject(testCase)
        verify(control)

        // Universal.Accent - enum
        control.Universal.accent = Universal.Red
        compare(control.Universal.accent, "#e51400")

        // Universal.Accent - string
        control.Universal.accent = "Emerald"
        compare(control.Universal.accent, "#008a00")

        // SVG named color
        control.Universal.accent = "tomato"
        compare(control.Universal.accent, "#ff6347")

        // #rrggbb
        control.Universal.accent = "#123456"
        compare(control.Universal.accent, "#123456")

        // #aarrggbb
        control.Universal.accent = "#12345678"
        compare(control.Universal.accent, "#12345678")

        // Qt.rgba() - no alpha
        control.Universal.accent = Qt.rgba(0.5, 0.5, 0.5)
        compare(control.Universal.accent, "#808080")

        // Qt.rgba() - with alpha
        control.Universal.accent = Qt.rgba(0.5, 0.5, 0.5, 0.5)
        compare(control.Universal.accent, "#80808080")

        // unknown
        ignoreWarning("QQuickUniversalStyle: unknown accent 123")
        control.Universal.accent = 123
        ignoreWarning("QQuickUniversalStyle: unknown accent \"foo\"")
        control.Universal.accent = "foo"
        ignoreWarning("QQuickUniversalStyle: unknown accent \"#1\"")
        control.Universal.accent = "#1"

        control.destroy()
    }
}