import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.rightMargin: 20 // make room for scrollbar
    implicitHeight: groupBox.height

    property alias title: groupBox.title
    property real rowSpacing: 20

    default property alias children: layout.children

    GroupBox {
        id: groupBox
        anchors.left: parent.left
        anchors.right: parent.right

        ColumnLayout {
            id: layout
            spacing: 15
        }
    }
}
