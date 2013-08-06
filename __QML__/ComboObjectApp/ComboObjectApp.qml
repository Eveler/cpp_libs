import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import "content"

ApplicationWindow {
    id: applicationWindow
    title: qsTr("Hello World")
    width: 500
    height: 300

    ComboObject {
        id: comboObject

        anchors.centerIn: parent

        width: contentWidth
        height: contentHeight

        fontBold: true
        fontPixelSize: 14
        fontFamily: "Pluto Bold"
        label: "Тип документа"
    }
}
