import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0

import com.mihail.clientsystem 1.0
import com.mihail.clientsystemsources 1.0


ApplicationWindow {
    width: 500
    height: 350

    Connections {
        target: AssessmentsSource
        onLastErrorChanged: {
            console.debug( AssessmentsSource.lastError )
        }
    }
}
