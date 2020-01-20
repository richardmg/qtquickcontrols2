import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ControlContainer {
    id: container
    title: "Buttons"

    Row {
        spacing: container.rowSpacing

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
        spacing: container.rowSpacing

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
        spacing: container.rowSpacing

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
