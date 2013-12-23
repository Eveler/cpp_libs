import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0

import com.mihail.clientsystem 1.0
import com.mihail.clientsystemsources 1.0
import extensions.mihail.mqmllibraries 1.0


ApplicationWindow {
    id: mainWindow
    width: 500
    height: 350

    Rectangle {
        anchors.fill: progressBar
        anchors.margins: -15

        radius: width/3
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
        width: 300
        height: 30

        progress: (ClientSystemSources.progress/100.0)
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
        ClientSystemSources.enqueue( ClientSystemSources.assessmentLoader )
        ClientSystemSources.enqueue( ClientSystemSources.assessmenttypeLoader )
        ClientSystemSources.enqueue( ClientSystemSources.callstatusLoader )
        ClientSystemSources.enqueue( ClientSystemSources.clientLoader )
        ClientSystemSources.enqueue( ClientSystemSources.declarLoader )
        ClientSystemSources.startQueue()
    }
}
