import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.impl 2.12

ControlContainer {
    title: "CheckBoxes"

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
}