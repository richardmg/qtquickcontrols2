import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ControlContainer {
    title: "SpinBoxes"
    Row {
        spacing: 5

        SpinBox {
            value: 1000
            to: 2000
            width: 80
        }

        SpinBox {
            value: 0
            enabled: false
        }

        SpinBox {
            width: 50
            value: 10
            from: 5
            to: 15
            property bool qqc2_style_small
        }

        SpinBox {
            width: 50
            value: 0
            property bool qqc2_style_mini
        }
    }

}
