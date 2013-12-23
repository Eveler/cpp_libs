import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0

import com.mihail.clientsystem 1.0
import com.mihail.clientsystemsources 1.0


ApplicationWindow {
    id: mainWindow
    width: 500
    height: 350

    BusyIndicator {
        anchors.centerIn: parent
        width: 50
        height: width

        running: ClientSystemSources.started
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

    Component.onCompleted: {
        ClientSystemSources.enqueue( ClientSystemSources.assessmentLoader )
        ClientSystemSources.enqueue( ClientSystemSources.assessmenttypeLoader )
        ClientSystemSources.enqueue( ClientSystemSources.callstatusLoader )
        ClientSystemSources.enqueue( ClientSystemSources.clientLoader )
        ClientSystemSources.startQueue()
    }
}
