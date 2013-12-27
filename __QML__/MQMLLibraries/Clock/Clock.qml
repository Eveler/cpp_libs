import QtQuick 2.2


Item {
    id: clock
    width: 512; height: 512

    property date clockTime: new Date()
    onClockTimeChanged: {
        obj_Information.hours = obj_Information.shift ? clockTime.getUTCHours() + Math.floor(obj_Information.shift) : clockTime.getHours()
        obj_Information.night = ( obj_Information.hours < 7 || obj_Information.hours > 19 )
        obj_Information.minutes = obj_Information.shift ? clockTime.getUTCMinutes() + ((obj_Information.shift % 1) * 60) : clockTime.getMinutes()
        obj_Information.seconds = clockTime.getUTCSeconds();
    }

    Image {
        id: background
        anchors.centerIn: parent
        width: parent.width
        height: width
        source: "images/background.png"
    }

    Item {
        x: 0
        y: 2*(width/512)
        width: parent.width
        height: width
        Image {
            anchors.centerIn: parent
            width: parent.width
            height: width

            source: "images/second-shadow.png"
            smooth: true
            rotation: obj_Information.seconds * 6
            Behavior on rotation {
                SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
            }
        }
    }
    Image {
        id: image_Second
        anchors.centerIn: parent
        width: parent.width
        height: width

        source: "images/second.png"
        smooth: true
        rotation: obj_Information.seconds * 6
        Behavior on rotation {
            SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
        }
    }

    Item {
        x: 0
        y: 4*(width/512)
        width: parent.width
        height: width
        Image {
            anchors.centerIn: parent
            width: parent.width
            height: width

            source: "images/hour-shadow.png"
            smooth: true
            rotation: (obj_Information.hours * 30) + (obj_Information.minutes * 0.5)
            Behavior on rotation {
                SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
            }
        }
    }
    Image {
        anchors.centerIn: parent
        width: parent.width
        height: width

        source: "images/hour.png"
        smooth: true
        rotation: (obj_Information.hours * 30) + (obj_Information.minutes * 0.5)
        Behavior on rotation {
            SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
        }
    }

    Item {
        x: 0
        y: 6*(width/512)
        width: parent.width
        height: width
        Image {
            anchors.centerIn: parent
            width: parent.width
            height: width

            source: "images/minute-shadow.png"
            smooth: true
            rotation: obj_Information.minutes * 6
            Behavior on rotation {
                SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
            }
        }
    }
    Image {
        anchors.centerIn: parent
        width: parent.width
        height: width

        source: "images/minute.png"
        smooth: true
        rotation: obj_Information.minutes * 6
        Behavior on rotation {
            SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
        }
    }

    Image {
        anchors.centerIn: parent
        width: parent.width
        height: width
        source: "images/center.png"
    }

    QtObject {
        id: obj_Information

        property int hours
        property int minutes
        property int seconds
        property real shift
        property bool night: false
    }
}
