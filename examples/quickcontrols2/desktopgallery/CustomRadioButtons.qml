import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.impl 2.12

ControlContainer {
    title: "RadioButtons"

    Row {
        spacing: 5

        RadioButton {
            id: customContentItem
            text: "Custom content item"
            contentItem: Text {
                text: customContentItem.text
                color: "green"
            }
        }

        RadioButton {
            id: customIndicator
            text: "Custom indicator"
            indicator: Rectangle {
                implicitWidth: 14
                implicitHeight: 14

                radius: width / 2
                color: customIndicator.down ? customIndicator.palette.light : customIndicator.palette.base
                border.width: 2
                border.color: "green"

                Rectangle {
                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 2
                    width: 5
                    height: 5
                    radius: width / 2
                    color: "green"
                    visible: customIndicator.checked
                }
            }
        }

        RadioButton {
            id: allCustom
            text: "All custom"

            contentItem: Text {
                text: allCustom.text
                color: "green"
            }

            indicator: Rectangle {
                implicitWidth: 14
                implicitHeight: 14

                radius: width / 2
                color: allCustom.down ? allCustom.palette.light : allCustom.palette.base
                border.width: 2
                border.color: "green"

                Rectangle {
                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 2
                    width: 5
                    height: 5
                    radius: width / 2
                    color: "green"
                    visible: allCustom.checked
                }
            }
        }
    }

}
