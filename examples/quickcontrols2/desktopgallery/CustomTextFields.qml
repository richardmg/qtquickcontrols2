import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ControlContainer {
    title: "TextFields"
    Row {
        spacing: 5

        TextField {
            placeholderText: "Custom background"
            background: Rectangle {
                implicitWidth: 130
                implicitHeight: 20
                border.width: control.activeFocus ? 2 : 1
                color: control.palette.base
                border.color: "green"
            }
        }
        TextField {
            placeholderText: "Large font"
            font.pixelSize: 20
        }
    }
}
