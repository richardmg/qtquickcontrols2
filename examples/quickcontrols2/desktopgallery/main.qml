import QtQuick 2.15
import QtQuick.Window 2.13
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("Desktop Gallery")

    ScrollView {
        anchors.fill: parent
        anchors.margins: 20
        contentWidth: width

        Column {
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 20

            Buttons { }
            CheckBoxes { }
            RadioButtons { }
            Sliders { }
        }
    }

}
