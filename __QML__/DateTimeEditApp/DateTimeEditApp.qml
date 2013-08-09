import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import "content"

ApplicationWindow {
    id: applicationWindow
    title: qsTr("Hello World")
    width: 500
    height: 300

    Item {
        anchors.fill: parent

        DateTimeEdit {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            width: contentWidth
            height: contentHeight

            fontBold: true
            fontPixelSize: 14
            fontFamily: "Consolas"
            label: "Дата выдачи"
        }

        Calendar {
            anchors.centerIn: parent

            poppedup: true
        }
    }
}
