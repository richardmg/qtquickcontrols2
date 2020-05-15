import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ControlContainer {
    title: "TextFields"
    Row {
        spacing: 5

        TextField {
            text: "Default"
        }

        TextField {
            enabled: false
            text: "Disabled"
        }

        TextField {
            placeholderText: "Placeholder text"
        }

        TextField {
            text: "Small"
            font.pixelSize: 11
            property bool qqc2_style_small
        }

        TextField {
            text: "Mini"
            font.pixelSize: 9
            property bool qqc2_style_mini
        }
    }
}
