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
            id: button_Flip
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            checkable: true

            text: "Flip"
        }

        Flipable {
            id: flipable
            anchors.centerIn: parent
            width: 500
            height: 240

            property bool flipped: button_Flip.checked

            front: Row {
                anchors.fill: parent
                spacing: 5

                DateButton {
                    id: docDate
                    width: parent.width*0.5
                    height: contentHeight

                    label: "Дата выдачи"
                    fontBold: true
                    fontPixelSize: 14
                    checkVisible: true

                    minimumDate: "2008-01-01"
                    replacementText: " "
                }

                DateButton {
                    id: docExpires
                    width: (parent.width*0.5)-parent.spacing
                    height: contentHeight

                    label: "действителен до"
                    fontBold: true
                    fontPixelSize: 14

                    minimumDate: "2008-01-01"
                    replacementText: " "
                }
            }


            back: Rectangle {
                anchors.fill: parent
                color: "black"
            }

            transform: Rotation {
                id: rotation
                origin.x: flipable.width/2
                origin.y: flipable.height/2
                axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
                angle: 0    // the default angle
            }

            states: State {
                name: "back"
                PropertyChanges { target: rotation; angle: 180 }
                when: flipable.flipped
            }

            transitions: Transition {
                NumberAnimation { target: rotation; property: "angle"; duration: 200 }
            }
        }
    }
}
