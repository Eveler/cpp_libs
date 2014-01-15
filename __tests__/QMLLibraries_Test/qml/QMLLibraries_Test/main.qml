import QtQuick 2.2
import QtQuick.Controls 1.1

import "OnOffButton"


Rectangle {
    width: 360
    height: 360

    color: "#ff555555"

//    OnOffButton {
//        anchors.centerIn: parent
//        width: parent.width*slider.value

//        circularIndicator: bt.checked
//    }

//    Slider {
//        id: slider
//        anchors.bottom: bt.top
//        anchors.bottomMargin: 10
//        width: parent.width

//        value: 0.2
//    }

//    OnOffButton {
//        id: bt
//        anchors.bottom: parent.bottom
//    }
    Image {
        anchors.fill: parent

        source: "page0.jpg"
        antialiasing: true
    }
}
