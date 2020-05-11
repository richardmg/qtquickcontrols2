import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.impl 2.12

ControlContainer {
    title: "RadioButtons"

    Row {
        spacing: 5

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
                property bool qqc2_style_small
            }
            RadioButton {
                text: "Mini"
                property bool qqc2_style_small
            }
            RadioButton {
                text: "Mini"
                property bool qqc2_style_small
            }
        }
    }

}
