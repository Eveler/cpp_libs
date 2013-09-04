import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0


Rectangle {
    id: toolBarButton
    color: "transparent"
    width: button.width

    property string text: ""

    signal clicked

    Button {
        id: button
        anchors.fill: parent
        scale: ( hovered ? 1.00 : 0.80 )
        Behavior on scale {
            NumberAnimation { duration: 200; easing.type: Easing.OutBack }
        }
        antialiasing: true

        opacity: ( toolBarButton.enabled ? 1.0 : 0.5 )

        text: toolBarButton.text
        style: ButtonStyle {
            label: Text{
                text: control.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                scale: ( control.hovered ? 1.2 : 1.4 )
                Behavior on scale {
                    NumberAnimation { duration: 200 }
                }
                color: ( control.hovered ? "#ff00ffff" : "#ffffffff" )
                Behavior on color {
                    ColorAnimation { duration: 200 }
                }
            }
            background: Rectangle {
                implicitWidth: toolBarButton.implicitWidth
                implicitHeight: toolBarButton.implicitHeight
                color: ( control.hovered ? "#12000000" : "transparent" )
                radius: 5
                Behavior on color {
                    ColorAnimation { duration: 200 }
                }
            }
        }
        RadialGradient {
            anchors.fill: parent
            source: parent
            gradient: Gradient {
                GradientStop { position: ( button.hovered ? 0.0 : 0.9 ); color: "white" }
                GradientStop { position: ( button.hovered ? 0.5 : 0.95 ); color: "black" }
            }
        }

        onClicked: clickAnimation.start()
    }
    DropShadow {
        anchors.fill: button
        horizontalOffset: 1
        verticalOffset: 1
        radius: 2.0
        samples: 16
        color: "black"
        scale: button.scale
        source: button

        opacity: ( toolBarButton.enabled ? 1.0 : 0.5 )
    }

    Text {
        id: clickedText
        anchors.centerIn: button
        visible: clickAnimation.running
        text: button.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"

        opacity: ( toolBarButton.enabled ? 1.0 : 0.5 )

        ParallelAnimation{
            id: clickAnimation

            NumberAnimation {
                target: clickedText
                property: "scale"
                from: 1.2
                to: ( clickedText.contentHeight*
                     (clickedText.parent.width/clickedText.contentWidth) >
                     clickedText.parent.height ?
                         (clickedText.parent.height/clickedText.contentHeight) :
                         (clickedText.parent.width/clickedText.contentWidth) )
                duration: 250
            }
            NumberAnimation {
                target: clickedText
                property: "opacity"
                from: 1.0
                to: 0.0
                duration: 250
            }

            onStopped: toolBarButton.clicked()
        }
    }
}
