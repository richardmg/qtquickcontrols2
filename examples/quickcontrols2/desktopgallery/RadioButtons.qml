import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.impl 2.12

ControlContainer {
    id: container
    title: "RadioButtons"

    Row {
        spacing: container.rowSpacing

        Column {
            RadioButton {
                text: "Default"
            }
            RadioButton {
                text: "Default"
            }
            RadioButton {
                text: "Default"
            }
        }

        Column {
            RadioButton {
                text: "Disabled"
                enabled: false
            }
            RadioButton {
                text: "Disabled"
                enabled: false
            }
            RadioButton {
                text: "Disabled"
                enabled: false
            }
        }

        Column {
            RadioButton {
                text: "Small"
                property bool qqc2_style_small
            }
            RadioButton {
                text: "Small"
                property bool qqc2_style_small
            }
            RadioButton {
                text: "Small"
                property bool qqc2_style_small
            }
        }

        Column {
            RadioButton {
                text: "Mini"
                property bool qqc2_style_mini
            }
            RadioButton {
                text: "Mini"
                property bool qqc2_style_mini
            }
            RadioButton {
                text: "Mini"
                property bool qqc2_style_mini
            }
        }
    }

}
