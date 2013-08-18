import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
//import com.mihail.qmlcomponents 1.0

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    
    Item {
        anchors.fill: parent

        Button {
            id: ch
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            checkable: true

            text: "Button"
        }

        DateButton {
            height: contentHeight

            anchors.centerIn: parent
        }
    }
}
