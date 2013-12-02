import QtQuick 2.0
import com.mihail.clientsystem 1.0


QtObject {
    property string lastError: ""
    property Item item: Item {
        Connections {
            target: UserLoader
            onErrorAdded: lastError = UserLoader.error( errorId )
        }
        Connections {
            target: ServiceLoader
            onErrorAdded: lastError = ServiceLoader.error( errorId )
        }
        Connections {
            target: ProcedureLoader
            onErrorAdded: lastError = ProcedureLoader.error( errorId )
        }
        Connections {
            target: RecipientLoader
            onErrorAdded: lastError = RecipientLoader.error( errorId )
        }
        Connections {
            target: ResultLoader
            onErrorAdded: lastError = ResultLoader.error( errorId )
        }
        Connections {
            target: ResultwayLoader
            onErrorAdded: lastError = ResultwayLoader.error( errorId )
        }
        Connections {
            target: AssessmentLoader
            onErrorAdded: lastError = AssessmentLoader.error( errorId )
        }
        Connections {
            target: AssessmenttypeLoader
            onErrorAdded: lastError = AssessmenttypeLoader.error( errorId )
        }

        Connections {
            target: DeclarClientLoader
            onErrorAdded: lastError = DeclarClientLoader.error( errorId )
        }

        Connections {
            target: TrusteeLoader
            onErrorAdded: lastError = TrusteeLoader.error( errorId )
        }

        Connections {
            target: ClientLoader
            onErrorAdded: lastError = ClientLoader.error( errorId )
        }
    }

    onLastErrorChanged: console.debug( lastError )
}
