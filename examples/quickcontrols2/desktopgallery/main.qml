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

        Column {
            spacing: 20

            Buttons { }
            Sliders { }
        }
    }

}
