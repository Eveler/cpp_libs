import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

import PyPlugin 1.0


ApplicationWindow {
    id: mainWindow
    width: 800
    height: 800

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

    MyClass {
        id: myClass
    }

    Button {
        text: "Кнопка"
        style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: control.activeFocus ? 2 : 1
                    border.color: "#888"
                    radius: 4
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                        GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                    }
                }
            }
        onClicked: myClass.p()
    }
}
