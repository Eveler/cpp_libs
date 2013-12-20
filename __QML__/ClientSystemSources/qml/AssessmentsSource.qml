pragma Singleton
import QtQuick 2.2

import com.mihail.clientsystem 1.0


Item {
    id: assessmentsSource



    readonly property AssessmentList assessmentList: obj_Information.assessmentList

    Component {
        id: componentAssessment

        Assessment {

        }
    }

    QtObject {
        id: obj_Information

        property AssessmentLoader assessmentLoader: AssessmentLoader{
            onNewInfo: {
                if ( componentAssessment.status === Component.Ready )
                {
                    var curItem = componentAssessment.createObject( componentAssessment )
                    assessmentList.add( curItem )
                }
                else console.debug( componentAssessment.errorString() )
                console.debug( info.name() )
            }
        }
        property AssessmentList assessmentList: AssessmentList{}
    }

    Component.onCompleted: obj_Information.assessmentLoader.load()
}
