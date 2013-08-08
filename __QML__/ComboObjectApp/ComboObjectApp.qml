import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import "content"

ApplicationWindow {
    id: applicationWindow
    title: qsTr("Hello World")
    width: 500
    height: 300

    Rectangle {
        anchors.fill: parent

        color: "#ff5599aa"
    }

    Item {
        anchors.fill: parent

        ComboObject {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top

            width: contentWidth
            height: contentHeight

            fontBold: true
            fontPixelSize: 14
            fontFamily: "Pluto Bold"
            label: "Тип документа"

        }

        ComboObject {
            anchors.centerIn: parent

            width: contentWidth
            height: contentHeight

            fontBold: true
            fontPixelSize: 14
            fontFamily: "Pluto Bold"
            label: "Тип документа"

        }
    }
}
