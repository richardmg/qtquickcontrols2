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
            width: sliderWidth
            from: 0
            to: 10
            value: 5
        }

        Slider {
            width: sliderWidth
            from: 0
            to: 10
            value: 5
            enabled: false
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
            to: 10
            value: 5
            enabled: false
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
    }
}
