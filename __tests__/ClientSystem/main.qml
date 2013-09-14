import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

import com.mihail.clientsystem 1.0


ApplicationWindow {
    width: 500
    height: 350

    Connections {
        target: UserLoader
        onErrorAdded: {
            console.debug( UserLoader.error( errorId ) )
        }
    }

    Connections {
        target: ProcedureLoader
        onErrorAdded: {
            console.debug( ProcedureLoader.error( errorId ) )
        }
    }

    Connections {
        target: RecipientLoader
        onErrorAdded: {
            console.debug( RecipientLoader.error( errorId ) )
        }
    }

    Connections {
        target: DepartmentLoader
        onErrorAdded: {
            console.debug( DepartmentLoader.error( errorId ) )
        }
    }

    Connections {
        target: DoctypeLoader
        onErrorAdded: {
            console.debug( DoctypeLoader.error( errorId ) )
        }
    }

    Connections {
        target: CallstatusLoader
        onErrorAdded: {
            console.debug( CallstatusLoader.error( errorId ) )
        }
    }

    Connections {
        target: HumanLoader
        onErrorAdded: {
            console.debug( HumanLoader.error( errorId ) )
        }
    }


    Item {
        anchors.fill: parent

        Button {
            anchors.centerIn: parent

            text: "Загрузка"

            onClicked: {
                progress.value = 0
                progress.max = 7
                progress.animated = true

                nextStatus( "Пользователи", UserLoader )
                nextStatus( "Наименования действий/процедур", ProcedureLoader )
                nextStatus( "Наименования адресатов", RecipientLoader )
                nextStatus( "Наименования местонахождений", DepartmentLoader )
                nextStatus( "Наименования документов", DoctypeLoader )
                nextStatus( "Наименования статусов звонка", CallstatusLoader )
                nextStatus( "Граждане", HumanLoader )
                progress.animated = false
            }

            function nextStatus( statusText, guideLoader ) {
                loadstatuses.append( {"statusText": statusText} )
                guideLoader.load()
                console.debug( statusText+": "+guideLoader.source.count )
                loadstatuses.remove( 0 )
                progress.value++
            }
        }
    }

    statusBar: Item {
        width: parent.width
        height: 30

        ListModel {
            id: loadstatuses
        }

        ListView {
            anchors.fill: parent

            clip: true
            orientation: ListView.Horizontal

            model: loadstatuses

            delegate: Text {
                width: contentWidth+6
                height: parent.height

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: statusText
            }

            add: Transition {
                ParallelAnimation {
                    NumberAnimation { properties: "x"; from: width; duration: 200 }
                    NumberAnimation { properties: "opacity"; from: 0.0; to: 1.0; duration: 200 }
                }
            }
            remove: Transition {
                ParallelAnimation {
                    NumberAnimation { properties: "x"; duration: 200 }
                    NumberAnimation { properties: "opacity"; from: 1.0; to: 0.0; duration: 1000 }
                }
            }
        }

        Rectangle {
            id: progress
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height
            width: ( max > 0 ? (value/max*parent.width) : 0 )
            Behavior on width {
                enabled: progress.animated
                NumberAnimation { duration: 200 }
            }

            property int value: 0
            property int max: 0
            property bool animated: false

            color: "#55000000"
        }
    }
}
