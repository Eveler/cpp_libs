import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0

import com.mihail.clientsystem 1.0
import com.mihail.clientsystemsources 1.0


ApplicationWindow {
    id: mainWindow
    width: 500
    height: 350

    Connections {
        target: ClientSystemSources.assessmentLoader
        onLastErrorChanged: {
            console.debug( ClientSystemSources.assessmentLoader.lastError )
        }
        onStartedChanged: {
            console.debug( ClientSystemSources.assessmentLoader.started )
            if ( !ClientSystemSources.assessmentLoader.started )
                ClientSystemSources.assessmenttypeLoader.load()
        }
    }
    Connections {
        target: ClientSystemSources.assessmenttypeLoader
        onLastErrorChanged: {
            console.debug( ClientSystemSources.assessmenttypeLoader.lastError )
        }
        onStartedChanged: {
            console.debug( ClientSystemSources.assessmenttypeLoader.started )
            if ( !ClientSystemSources.assessmenttypeLoader.started )
                ClientSystemSources.callstatusLoader.load()
        }
    }
    Connections {
        target: ClientSystemSources.callstatusLoader
        onLastErrorChanged: {
            console.debug( ClientSystemSources.callstatusLoader.lastError )
        }
        onStartedChanged: {
            console.debug( ClientSystemSources.callstatusLoader.started )
        }
    }

    Component.onCompleted: {
        console.debug( ClientSystemSources )
        ClientSystemSources.assessmentLoader.load()
    }
}
