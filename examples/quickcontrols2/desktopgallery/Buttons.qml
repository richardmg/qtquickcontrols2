import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ControlContainer {
    title: "Buttons"
    Row {
        spacing: 5

        Button {
            text: "Default"
        }

        Button {
            text: "Disabled"
            enabled: false
        }

        Button {
            text: "Small"
            property bool qqc2_style_small
        }

        Button {
            text: "Mini"
            property bool qqc2_style_mini
        }
    }

    Row {
        spacing: 5

        Button {
            text: "Explicit height"
            height: 50
        }

        Button {
            text: "Explicit width"
            width: 200
        }
    }

    Row {
        spacing: 5

        Button {
            text: "Highlighted"
            highlighted: true
        }

        Button {
            text: "Flat"
            flat: true
        }
    }
}
