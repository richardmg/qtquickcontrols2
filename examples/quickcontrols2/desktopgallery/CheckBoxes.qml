import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    implicitWidth: groupBox.width
    implicitHeight: groupBox.height

    GroupBox {
        id: groupBox
        title: "Checkboxes"

        ColumnLayout {
            spacing: 15

            Row {
                spacing: 5

                CheckBox {
                    text: "Default button"
                }
            }

        }
    }
}
