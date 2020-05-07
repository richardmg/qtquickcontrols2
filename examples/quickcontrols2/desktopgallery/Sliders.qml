import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ControlContainer {
    title: "Sliders"
    property int sliderWidth: 400
    property int sliderHeight: 220

    Column {
        spacing: 5

        Slider {
            id: control
            width: sliderWidth
            from: 0
            to: 10
            value: 5
        }

        Slider {
            width: sliderWidth
            from: 0
            to: 100
            value: 20
            stepSize: 20

            property int qqc2_style_tickPosition: 1
        }

        Slider {
            width: sliderWidth
            from: 0
            to: 100
            stepSize: 5
            value: 65

            property int qqc2_style_tickPosition: 2
        }

        Slider {
            id: customHandle
            width: sliderWidth
            height: 20
            from: 0
            to: 10
            value: 5
            handle: Rectangle {
                id: handle
                width: 12
                height: customHandle.height
                color: "white"
                border.width: 2

                x: customHandle.visualPosition * (customHandle.availableWidth - width)
                y: (customHandle.availableHeight - height) / 2
            }
        }

        Slider {
            id: customBackground
            width: sliderWidth
            from: 0
            to: 10
            background: Rectangle {
                implicitHeight: 5
                color: "lightgray"
                border.width: 1
            }
        }

        Slider {
            id: customAll
            width: sliderWidth
            height: 20
            from: 0
            to: 10
            background: Rectangle {
                implicitHeight: customAll.height
                color: "lightgray"
                border.width: 1
            }
            handle: Rectangle {
                width: 12
                height: customAll.height
                color: "white"
                border.width: 2

                x: customAll.visualPosition * (customAll.availableWidth - width)
                y: (customAll.availableHeight - height) / 2
            }
        }
    }

    Row {
        spacing: 5

        Slider {
            height: sliderHeight
            orientation: Qt.Vertical
            from: 0
            to: 10
            value: 5
        }

        Slider {
            height: sliderHeight
            orientation: Qt.Vertical
            from: 0
            to: 100
            value: 20
            stepSize: 20

            property int qqc2_style_tickPosition: 1
        }

        Slider {
            height: sliderHeight
            orientation: Qt.Vertical
            from: 0
            to: 100
            stepSize: 5
            value: 65

            property int qqc2_style_tickPosition: 2
        }

        Slider {
            id: customVHandle
            width: 20
            height: sliderHeight
            orientation: Qt.Vertical
            from: 0
            to: 10
            value: 5
            handle: Rectangle {
                height: 12
                width: customVHandle.width
                color: "white"
                border.width: 2

                x: (customVHandle.availableWidth - width) / 2
                y: customVHandle.visualPosition * (customVHandle.availableHeight - height)
            }
        }

        Slider {
            id: customVBackground
            height: sliderHeight
            orientation: Qt.Vertical
            from: 0
            to: 10
            background: Rectangle {
                implicitWidth: 5
                color: "lightgray"
                border.width: 1
            }
        }

        Slider {
            id: customVAll
            width: 20
            height: sliderHeight
            orientation: Qt.Vertical
            from: 0
            to: 10
            value: 5
            handle: Rectangle {
                height: 12
                width: customVHandle.width
                color: "white"
                border.width: 2

                x: (customVAll.availableWidth - width) / 2
                y: customVAll.visualPosition * (customVAll.availableHeight - height)
            }
            background: Rectangle {
                implicitWidth: 5
                color: "lightgray"
                border.width: 1
            }
        }
    }
}
