import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0

ColumnLayout {
    id: zoomTools

    readonly property real scaleValue: pageScaler.value

    Slider {
        id: pageScaler
        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        Layout.fillHeight: true

        orientation: Qt.Vertical

        style: SliderStyle {
            handle: Rectangle {
                anchors.centerIn: parent
                color: control.pressed ? "white" : "lightgray"
                border.color: "gray"
                border.width: 2
                width: 24
                height: 32
                radius: 5

                Text {
                    anchors.fill: parent

                    rotation: 90
                    readonly property int val: control.value*100
                    text: val+"%"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        value: 1.00
        minimumValue: 0.01
        maximumValue: 10.00
        stepSize: 0.01
        updateValueWhileDragging: true

        NumberAnimation {
            id: sliderMoving
            target: pageScaler
            property: "value"

            duration: 100
        }
    }

    Rectangle {
        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        width: 32
        height: 24

        radius: 5
        color: ( zoomInMouse.containsMouse ? "#25ffffff" : "#55ffffff" )

        Image {
            anchors.fill: parent
            anchors.margins: 2

            fillMode: Image.PreserveAspectFit
            source: "qrc:/images/Zoom_in.png"
        }

        MouseArea {
            id: zoomInMouse
            anchors.fill: parent

            hoverEnabled: true

            onClicked: {
                sliderMoving.from = pageScaler.value
                sliderMoving.to = pageScaler.value+( pageScaler.value > 1.49 ? 0.5 : 0.1 )
                sliderMoving.start()
            }
        }
    }

    Rectangle {
        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        width: 32
        height: 24

        radius: 5
        color: ( zoomOutMouse.containsMouse ? "#25ffffff" : "#55ffffff" )

        Image {
            anchors.fill: parent
            anchors.margins: 2

            fillMode: Image.PreserveAspectFit
            source: "qrc:/images/Zoom_out.png"
        }

        MouseArea {
            id: zoomOutMouse
            anchors.fill: parent

            hoverEnabled: true

            onClicked: {
                sliderMoving.from = pageScaler.value
                sliderMoving.to = pageScaler.value-( pageScaler.value > 1.49 ? 0.5 : 0.1 )
                sliderMoving.start()
            }
        }
    }

    Rectangle {
        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        width: 32
        height: 24

        radius: 5
        color: ( zoomDefaultMouse.containsMouse ? "#25ffffff" : "#55ffffff" )

        Text {
            anchors.fill: parent

            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            font.pixelSize: 10
            text: "100%"
        }

        MouseArea {
            id: zoomDefaultMouse
            anchors.fill: parent

            hoverEnabled: true

            onClicked: {
                sliderMoving.from = pageScaler.value
                sliderMoving.to = 1.00
                sliderMoving.start()
            }
        }
    }

    Rectangle {
        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        width: 32
        height: 24

        radius: 5
        color: ( zoomExpandMouse.containsMouse ? "#25ffffff" : "#55ffffff" )

        Image {
            anchors.fill: parent
            anchors.margins: 2

            fillMode: Image.PreserveAspectFit
            source: "qrc:/images/Expand.png"
        }

        MouseArea {
            id: zoomExpandMouse
            anchors.fill: parent

            hoverEnabled: true

            onClicked: {
                sliderMoving.from = pageScaler.value
                sliderMoving.to = zoomValueForExpand()
                sliderMoving.start()
            }

            function zoomValueForExpand()
            {
                var result = 0.0
                if ( page.sourceSize.width*
                        (mainContainer.height/page.sourceSize.height) >
                        mainContainer.width-(mainContainer.borderWidth*2) )
                    result = (mainContainer.width-(mainContainer.borderWidth*2))/page.sourceSize.width
                else
                    result = mainContainer.height/page.sourceSize.height
                return result
            }
        }
    }
}
