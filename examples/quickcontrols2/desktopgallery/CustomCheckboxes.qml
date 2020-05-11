import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.impl 2.12

ControlContainer {
    title: "CheckBoxes"

    Row {
        spacing: 5

        CheckBox {
            id: customContentItem
            text: "Custom content item"
            contentItem: Text {
                text: customContentItem.text
                color: "green"
            }
        }

        CheckBox {
            id: customIndicator
            text: "Custom indicator"
            indicator: Rectangle {
                implicitWidth: 15
                implicitHeight: 15

                color: customIndicator.down ? customIndicator.palette.light : customIndicator.palette.base
                border.color: "green"
                border.width: 2

                ColorImage {
                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 2
                    defaultColor: "#353637"
                    scale: 0.5
                    color: customIndicator.palette.text
                    source: "qrc:/qt-project.org/imports/QtQuick/Controls.2/images/check.png"
                    visible: customIndicator.checkState === Qt.Checked
                }

                Rectangle {
                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 2
                    width: 16
                    height: 3
                    color: customIndicator.palette.text
                    visible: customIndicator.checkState === Qt.PartiallyChecked
                }
            }
        }

        CheckBox {
            id: allCustom
            text: "All custom"

            contentItem: Text {
                text: allCustom.text
                color: "green"
            }

            indicator: Rectangle {
                implicitWidth: 15
                implicitHeight: 15

                color: allCustom.down ? allCustom.palette.light : allCustom.palette.base
                border.color: "green"
                border.width: 2

                ColorImage {
                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 2
                    defaultColor: "#353637"
                    scale: 0.5
                    color: allCustom.palette.text
                    source: "qrc:/qt-project.org/imports/QtQuick/Controls.2/images/check.png"
                    visible: allCustom.checkState === Qt.Checked
                }

                Rectangle {
                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 2
                    width: 16
                    height: 3
                    color: allCustom.palette.text
                    visible: allCustom.checkState === Qt.PartiallyChecked
                }
            }
        }
    }
}
