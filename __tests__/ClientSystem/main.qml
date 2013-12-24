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
        anchors.top: progressBar.bottom
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
        ClientSystemSources.enqueue( ClientSystemSources.assessmentLoader )
        ClientSystemSources.enqueue( ClientSystemSources.assessmenttypeLoader )
        ClientSystemSources.enqueue( ClientSystemSources.callstatusLoader )
        ClientSystemSources.enqueue( ClientSystemSources.clientLoader )
        ClientSystemSources.enqueue( ClientSystemSources.declarLoader )
        ClientSystemSources.startQueue()
    }
}
