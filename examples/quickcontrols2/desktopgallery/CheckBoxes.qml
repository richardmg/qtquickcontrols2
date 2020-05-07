import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.impl 2.12

ControlContainer {
    Row {
        spacing: 5

        CheckBox {
            text: "Default"
        }

        CheckBox {
            text: "Tri-state"
            tristate: true
        }

        CheckBox {
            text: "Small"
            property bool qqc2_style_small
        }

        CheckBox {
            text: "Mini"
            property bool qqc2_style_mini
        }
    }

    Row {
        spacing: 5

        CheckBox {
            id: customContentItem
            text: "Custom content item"
            contentItem: CheckLabel {
                leftPadding: customContentItem.indicator.width + customContentItem.spacing
                rightPadding: customContentItem.indicator.width + customContentItem.spacing
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

                x: customIndicator.text ? (customIndicator.mirrored ? customIndicator.width - width - customIndicator.rightPadding : customIndicator.leftPadding) : customIndicator.leftPadding + (customIndicator.availableWidth - width) / 2
                y: customIndicator.topPadding + (customIndicator.availableHeight - height) / 2

                color: customIndicator.down ? customIndicator.palette.light : customIndicator.palette.base
                border.width: 2
                border.color: "green"

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

            contentItem: CheckLabel {
                leftPadding: allCustom.indicator.width + allCustom.spacing
                rightPadding: allCustom.indicator.width + allCustom.spacing
                text: allCustom.text
                color: "green"
            }

            indicator: Rectangle {
                implicitWidth: 15
                implicitHeight: 15

                x: allCustom.text ? (allCustom.mirrored ? allCustom.width - width - allCustom.rightPadding : allCustom.leftPadding) : allCustom.leftPadding + (allCustom.availableWidth - width) / 2
                y: allCustom.topPadding + (allCustom.availableHeight - height) / 2

                color: allCustom.down ? allCustom.palette.light : allCustom.palette.base
                border.width: 2
                border.color: "green"

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
