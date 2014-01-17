import QtQuick 2.2
import QtGraphicalEffects 1.0


Item {
    id: onoffButton
    width: 100
    height: width

    property bool checked: false
    property bool circularIndicator: false
    property real textPercentSize: 0.25
    property bool textVisible: true


    Item {
        anchors.right: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: height*0.5
        height: parent.width

        visible: !onoffButton.circularIndicator


        Rectangle {
            id: rect_LeftBackground
            anchors.horizontalCenter: parent.right
            anchors.verticalCenter: parent.verticalCenter
            width: height
            height: parent.height

            radius: width*0.5
            visible: false
        }

        LinearGradient {
            id: lgrad_LeftBackground
            anchors.fill: parent

            start: Qt.point(0, 0)
            end: Qt.point(0, height)
            source: rect_LeftBackground
            visible: false
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: ( !onoffButton.checked ? "#ffff5511" : "#ff555555" )
                    Behavior on color { ColorAnimation { duration: 150 } }
                }
                GradientStop {
                    position: 1.0
                    color: ( !onoffButton.checked ? "#ffee4400" : "#ff333333" )
                    Behavior on color { ColorAnimation { duration: 150 } }
                }
            }
        }

        InnerShadow {
            id: ishadow_LeftBackground
            anchors.fill: lgrad_LeftBackground
            radius: width*0.1
            samples: 16
            horizontalOffset: 1
            color: "#b0000000"
            source: lgrad_LeftBackground
        }
    }

    Item {
        anchors.left: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: height*0.5
        height: parent.width

        visible: !onoffButton.circularIndicator


        Rectangle {
            id: rect_RightBackground
            anchors.horizontalCenter: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: height
            height: parent.height

            radius: width*0.5
            visible: false
        }

        LinearGradient {
            id: lgrad_RightBackground
            anchors.fill: parent

            start: Qt.point(0, 0)
            end: Qt.point(0, height)
            source: rect_RightBackground
            visible: false
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: ( onoffButton.checked ? "#ff11ff55" : "#ff555555" )
                    Behavior on color { ColorAnimation { duration: 150 } }
                }
                GradientStop {
                    position: 1.0
                    color: ( onoffButton.checked ? "#ff00ee44" : "#ff333333" )
                    Behavior on color { ColorAnimation { duration: 150 } }
                }
            }
        }

        InnerShadow {
            id: ishadow_RightBackground
            anchors.fill: lgrad_RightBackground
            radius: width*0.1
            samples: 16
            horizontalOffset: -1
            color: "#b0000000"
            source: lgrad_RightBackground
        }
    }

    Item {
        anchors.right: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: height*0.5
        height: parent.width

        clip: true
        visible: onoffButton.circularIndicator


        Rectangle {
            id: rect_LeftBackground2
            anchors.horizontalCenter: parent.right
            anchors.verticalCenter: parent.verticalCenter
            width: height
            height: parent.height

            radius: width*0.5
            visible: false
        }

        ConicalGradient {
            id: cgrad_LeftBackground
            anchors.fill: rect_LeftBackground2

            source: rect_LeftBackground2
            angle: 0.0
            visible: false
            gradient: Gradient {
                GradientStop { position: 1.0; color: "transparent" }
                GradientStop { position: 0.9001; color: "transparent" }
                GradientStop { position: 0.9; color: "#ffff5511" }
                GradientStop {
                    position: ( !onoffButton.checked ? 0.6 : 0.8999 )
                    Behavior on position { NumberAnimation { duration: 350 } }
                    color: "#ffee4400"
                }
                GradientStop {
                    position: ( !onoffButton.checked ? 0.5999 : 0.8998 )
                    Behavior on position { NumberAnimation { duration: 350 } }
                    color: "#ff555555"
                }
                GradientStop { position: 0.5999; color: "#ff333333" }
                GradientStop { position: 0.5998; color: "transparent" }
                GradientStop { position: 0.5; color: "transparent" }
            }
        }

        InnerShadow {
            anchors.fill: cgrad_LeftBackground
            radius: width*0.1
            samples: 16
            horizontalOffset: 1
            color: "#b0000000"
            source: cgrad_LeftBackground
        }
    }

    Item {
        anchors.left: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: height*0.5
        height: parent.width

        clip: true
        visible: onoffButton.circularIndicator


        Rectangle {
            id: rect_RightBackground2
            anchors.horizontalCenter: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: height
            height: parent.height

            radius: width*0.5
            visible: false
        }

        ConicalGradient {
            id: cgrad_RightBackground
            anchors.fill: rect_RightBackground2

            source: rect_RightBackground2
            angle: 0.0
            visible: false
            gradient: Gradient {
                GradientStop { position: 0.0; color: "transparent" }
                GradientStop { position: 0.0999; color: "transparent" }
                GradientStop { position: 0.1; color: "#ff11ff55" }
                GradientStop {
                    position: ( onoffButton.checked ? 0.4 : 0.1001 )
                    Behavior on position { NumberAnimation { duration: 350 } }
                    color: "#ff00ee44"
                }
                GradientStop {
                    position: ( onoffButton.checked ? 0.4001 : 0.1002 )
                    Behavior on position { NumberAnimation { duration: 350 } }
                    color: "#ff555555"
                }
                GradientStop { position: 0.4001; color: "#ff333333" }
                GradientStop { position: 0.4002; color: "transparent" }
                GradientStop { position: 0.5; color: "transparent" }
            }
        }

        InnerShadow {
            anchors.fill: cgrad_RightBackground
            radius: width*0.1
            samples: 16
            horizontalOffset: -1
            color: "#b0000000"
            source: cgrad_RightBackground
        }
    }

    Item {
        id: i_Button
        x: parent.width/2-width/2
        y: parent.height/2-height/2
        width: parent.width*0.8
        height: width


        Rectangle {
            id: rect_ButtonBackground
            anchors.fill: parent

            radius: width*0.5
            color: ( mouse_Button.containsMouse ? "#ffffffff" : "#ffbbbbbb" )
            Behavior on color { ColorAnimation { duration: 150 } }
        }
        RadialGradient {
            anchors.fill: parent
            anchors.margins: 1

            source: rect_ButtonBackground
            verticalOffset: width*0.4

            gradient: Gradient {
                GradientStop {
                    position: 0.0;
                    color: ( mouse_Button.containsMouse ? "#ffeeeeee" : "#ffaaaaaa" )
                    Behavior on color { ColorAnimation { duration: 150 } }
                }
                GradientStop {
                    position: 0.7
                    color: ( mouse_Button.containsMouse ? "#ffffffff" : "#ffdddddd" )
                    Behavior on color { ColorAnimation { duration: 150 } }
                }
            }
        }

        Text {
            id: text_ButtonLabel
            anchors.centerIn: parent
            width: contentWidth
            height: contentHeight

            visible: onoffButton.textVisible
            text: ( onoffButton.checked ? "Вкл" : "Выкл" )
            font.bold: true
            font.letterSpacing: 0
            color: "#ff555555"
            font.pixelSize: onoffButton.height*onoffButton.textPercentSize
        }

        MouseArea {
            id: mouse_Button
            anchors.fill: parent

            hoverEnabled: true

            onClicked: onoffButton.checked = !onoffButton.checked
        }
    }
}
