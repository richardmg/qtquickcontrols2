import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ControlContainer {
    title: "SpinBoxes"
    Row {
        spacing: 5

        SpinBox {
            id: custombg
            value: 1000
            to: 2000
            width: 80
            background: Rectangle {
                border.color: "green"
            }
        }

        SpinBox {
            id: customIndicator
            value: 1000
            to: 2000
            width: 80
            height: 28

            rightPadding: 17

            up.indicator: Rectangle {
                x: customIndicator.width - width - 4
                y: 3
                implicitWidth: customIndicator.rightPadding - 4
                implicitHeight: width - 2
                border.width: 1
                border.color: "green"
                color: customIndicator.up.pressed ? "gray" : "transparent"
                Text {
                    text: "+"
                    font.pixelSize: 8
                    font.bold: true
                    anchors.centerIn: parent
                }
            }

            down.indicator: Rectangle {
                x: customIndicator.width - width - 4
                y: height + 2
                implicitWidth: customIndicator.rightPadding - 4
                implicitHeight: width - 2
                border.width: 1
                border.color: "green"
                color: customIndicator.down.pressed ? "gray" : "transparent"
                Text {
                    text: "-"
                    font.pixelSize: 10
                    font.bold: true
                    anchors.centerIn: parent
                }
            }
        }

        SpinBox {
            id: allCustom
            value: 1000
            to: 2000
            width: 80
            height: 28

            rightPadding: 17

            background: Rectangle {
                border.color: "green"
            }

            up.indicator: Rectangle {
                x: allCustom.width - width - 4
                y: 3
                implicitWidth: allCustom.rightPadding - 4
                implicitHeight: width - 2
                border.width: 1
                border.color: "green"
                color: allCustom.up.pressed ? "gray" : "transparent"
                Text {
                    text: "+"
                    font.pixelSize: 8
                    font.bold: true
                    anchors.centerIn: parent
                }
            }

            down.indicator: Rectangle {
                x: allCustom.width - width - 4
                y: height + 2
                implicitWidth: allCustom.rightPadding - 4
                implicitHeight: width - 2
                border.width: 1
                border.color: "green"
                color: allCustom.down.pressed ? "gray" : "transparent"
                Text {
                    text: "-"
                    font.pixelSize: 10
                    font.bold: true
                    anchors.centerIn: parent
                }
            }
        }

    }

}
