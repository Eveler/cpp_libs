import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0

import com.mihail.clientsystem 1.0
import com.mihail.clientsystemsources 1.0
import extensions.mihail.mqmllibraries 1.0


ApplicationWindow {
    id: mainWindow
    width: 800
    height: 800

    Rectangle {
        id: background
        anchors.fill: parent

        color: "#ff666666"
    }

    BusyIndicator {
        anchors.verticalCenter: progressBar.verticalCenter
        anchors.left: progressBar.right
        anchors.leftMargin: 40
        width: progressBar.height
        height: width

        running: ClientSystemSources.progress <= 0
    }

    PointedProgressBar {
        id: progressBar
        anchors.centerIn: parent
        width: height*10
        height: 35

        progress: (ClientSystemSources.progress/100.0)
    }

    Rectangle {
        id: clockBackground
        anchors.top: clockLabel.top
        anchors.left: clock.left
        anchors.bottom: dateLabel.bottom
        anchors.right: clock.right
        anchors.margins: -15

        color: "#99dddddd"
        border.width: 3
        border.color: "#ff555555"
    }
    Text {
        id: clockLabel
        anchors.top: background.top
        anchors.topMargin: 55
        anchors.horizontalCenter: progressBar.horizontalCenter
        color: "white"
        font.family: "Helvetica"
        font.bold: true; font.pixelSize: 16
        style: Text.Raised; styleColor: "black"

        text: "ВРЕМЯ СЕРВЕРА"
    }
    Clock {
        id: clock
        anchors.top: clockLabel.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: clockLabel.horizontalCenter
        width: 256
        height: width

        Timer {
            id: clockTimer
            interval: 100
            running: true
            repeat: true
            onTriggered: clock.clockTime = MQML.addMSecs( new Date(), serverTimeCheck.diff )
        }
    }
    Text {
        id: dateLabel
        anchors.top: clock.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: clock.horizontalCenter
        color: "white"
        font.family: "Helvetica"
        font.bold: true; font.pixelSize: 16
        style: Text.Raised; styleColor: "black"

        text: Qt.formatDate( clock.clockTime, "MMMM dd yyyyг." )
    }
    Timer {
        id: serverTimeCheck
        interval: 600000

        property int diff: 0

        onTriggered: {
            diff = MQML.millisecondsBetween( new Date(), Database.serverTime() )
            start()
        }
    }

    Slider {
        id: slider
        width: 200
        anchors.bottom: rect_1.top
    }
    Rectangle {
        id: rect_1
        anchors.bottom: background.bottom
        anchors.horizontalCenter: background.horizontalCenter
        width: 200
        height: width
        radius: width/2

        visible: false
    }
    ConicalGradient {
        id: cgrad_1
        anchors.fill: rect_1

        source: rect_1
        angle: 0.0
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#ffff7733" }
            GradientStop { position: slider.value; color: "#ffdd5511" }
            GradientStop { position: (slider.value+0.0001); color: "transparent" }
        }

        visible: false
    }
    DropShadow {
        id: dshadow_3
        anchors.fill: cgrad_1
        verticalOffset: 1
        radius: 1.0
        samples: 16
        color: "#80000000"
        source: cgrad_1
    }
    InnerShadow {
        anchors.fill: cgrad_1
        radius: 3.0
        samples: 16
        verticalOffset: 1
        color: "#ffffaa55"
        source: cgrad_1
    }
    Rectangle {
        id: rect_2
        anchors.centerIn: rect_1
        width: rect_1.width/2
        height: width

        radius: width/2
        color: "#ffdddddd"
        visible: false
    }
    DropShadow {
        anchors.fill: rect_2
        verticalOffset: 2
        radius: 1.0
        samples: 16
        color: "#80000000"
        source: rect_2
    }
    InnerShadow {
        id: iShadow_1
        anchors.fill: rect_2
        radius: 3.0
        samples: 16
        verticalOffset: 2
        color: "#ffffffff"
        source: rect_2
        visible: false
    }
    InnerShadow {
        anchors.fill: iShadow_1
        radius: 3.0
        samples: 16
        verticalOffset: -1
        color: "#ffaaaaaa"
        source: iShadow_1
    }
    Text {
        anchors.centerIn: rect_2

        property int value: (slider.value*100)
        text: value+"%"
        color: "#ffff7733"
        font.pixelSize: 24
        font.bold: true
        style: Text.Raised
        styleColor: "#ffaaaaaa"
    }


    Connections {
        target: ClientSystemSources

        onStartedChanged: {
            if ( !ClientSystemSources.started )
            {
                clock.clockTime = Database.serverTime()
                serverTimeCheck.start()
            }
            else serverTimeCheck.stop()
        }
    }

    Connections {
        target: ClientSystemSources.assessmentLoader

        onLastErrorChanged: console.debug( ClientSystemSources.assessmentLoader.lastError )
    }
    Connections {
        target: ClientSystemSources.assessmenttypeLoader

        onLastErrorChanged: console.debug( ClientSystemSources.assessmenttypeLoader.lastError )
    }
    Connections {
        target: ClientSystemSources.callstatusLoader

        onLastErrorChanged: console.debug( ClientSystemSources.callstatusLoader.lastError )
    }
    Connections {
        target: ClientSystemSources.clientLoader

        onLastErrorChanged: console.debug( ClientSystemSources.clientLoader.lastError )
    }
    Connections {
        target: ClientSystemSources.declarLoader

        onLastErrorChanged: console.debug( ClientSystemSources.declarLoader.lastError )
    }

    Component.onCompleted: {
        serverTimeCheck.diff = MQML.millisecondsBetween( new Date(), Database.serverTime() )
//        ClientSystemSources.enqueue( ClientSystemSources.assessmentLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.assessmenttypeLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.callstatusLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.clientLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.declarLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.declarLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.declarClientLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.departmentLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.doctypeLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.humanLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.organisationLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.procedureLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.recipientLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.resultLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.resultwayLoader )
//        ClientSystemSources.enqueue( ClientSystemSources.serviceLoader )
        ClientSystemSources.startQueue()
    }
}
