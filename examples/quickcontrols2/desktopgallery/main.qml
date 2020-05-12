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
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20
        anchors.rightMargin: 40

        TabButton {
            text: qsTr("Default controls")
        }

        TabButton {
            text: qsTr("Customized controls")
        }
    }

    StackLayout {
        currentIndex: bar.currentIndex
        anchors.top: bar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20

        ScrollView {
            contentWidth: width
            clip: true
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn

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

        ScrollView {
            contentWidth: width
            clip: true
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn

            Column {
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: 20

                CustomButtons { }
                CustomCheckBoxes { }
                CustomRadioButtons { }
                CustomSliders { }
            }
        }
    }

}
