import QtQuick 2.15
import QtQuick.Window 2.13
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("Desktop Gallery")

    TabBar {
        id: bar
        width: parent.width
        TabButton {
            text: qsTr("Buttons")
        }
        TabButton {
            text: qsTr("Sliders")
        }
        TabButton {
            text: qsTr("Misc")
        }
    }

    StackLayout {
        anchors.top: bar.bottom
        width: parent.width
        currentIndex: bar.currentIndex
        ButtonsTab { }
        SlidersTab { }
        Item { }
    }

}
