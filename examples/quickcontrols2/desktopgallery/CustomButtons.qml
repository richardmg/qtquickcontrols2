import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ControlContainer {
    title: "Buttons"

    Row {
        spacing: 5

        Button {
            id: buttonWithCustomContentItem
            text: "Custom contentItem"
            contentItem: Rectangle {
                implicitWidth: 120
                implicitHeight: il.implicitHeight
                color: buttonWithCustomContentItem.pressed ? "lightBlue" : "orange"
                Text {
                    id: il
                    text: buttonWithCustomContentItem.text
                    anchors.centerIn: parent
                }
            }
        }

        Button {
            id: cb
            text: "Custom background"
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 30
                radius: 5
                color: cb.pressed ? "LightGray" : "gray"
            }
        }

        Button {
            id: cb2
            text: "All custom"
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 30
                radius: 5
                color: cb2.pressed ? "LightGray" : "gray"
            }
            contentItem: Rectangle {
                implicitWidth: il2.implicitWidth
                implicitHeight: il2.implicitHeight
                radius: 3
                color: "lightgray"
                Text {
                    id: il2
                    text: cb2.text
                    anchors.centerIn: parent
                }
            }
        }
    }
}
