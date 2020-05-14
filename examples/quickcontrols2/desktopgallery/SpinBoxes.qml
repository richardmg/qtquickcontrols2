import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ControlContainer {
    title: "SpinBoxes"
    Row {
        spacing: 5

        SpinBox {
            value: 500
            to: 2000
        }

        SpinBox {
            value: 0
            enabled: false
        }

        SpinBox {
            value: 5
            from: 0
            to: 9
            property bool qqc2_style_small
        }

        SpinBox {
            value: 0
            from: -9
            to: 9
            property bool qqc2_style_mini
        }
    }

}
