import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

Button {
    id: borderButton
    property int buttonRotation: 0
    property string imageSource: ""

    style: ButtonStyle {
        label: Item {
            anchors.fill: parent

            Rectangle {
                anchors.fill: parent
                radius: 5

                color: ( control.hovered ? "#aa000000" : "#55000000" )
                Behavior on color {
                    ColorAnimation { duration: 100 }
                }
            }
            Text {
                id: buttonText
                rotation: borderButton.buttonRotation
                anchors.centerIn: parent

                text: control.text
                color: "white"
                font.pixelSize: 24
                font.bold: true
            }
            Image {
                anchors.top: parent.top
                anchors.left: parent.left
                height: borderButton.height-((borderButton.height/2)+(buttonText.width/2))
                anchors.right: parent.right
                rotation: borderButton.buttonRotation

                source: borderButton.imageSource
                fillMode: Image.PreserveAspectFit
            }
            Image {
                anchors.left: parent.left
                height: borderButton.height-((borderButton.height/2)+(buttonText.width/2))
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                rotation: borderButton.buttonRotation

                source: borderButton.imageSource
                fillMode: Image.PreserveAspectFit
            }
        }
        background: Rectangle {
            color: "transparent"
        }
    }
}
