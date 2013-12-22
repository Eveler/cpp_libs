pragma Singleton
import QtQuick 2.2

import com.mihail.clientsystem 1.0


Item {
    id: clientSystemSources

    readonly property bool started: ( assessmentLoader.started ||
                                     assessmenttypeLoader.started ||
                                     callstatusLoader.started )

    readonly property AssessmentList assessmentList: obj_Information.assessmentList
    readonly property AssessmentLoader assessmentLoader: obj_Information.assessmentLoader

    readonly property AssessmenttypeList assessmenttypeList: obj_Information.assessmenttypeList
    readonly property AssessmenttypeLoader assessmenttypeLoader: obj_Information.assessmenttypeLoader

    readonly property CallstatusList callstatusList: obj_Information.callstatusList
    readonly property CallstatusLoader callstatusLoader: obj_Information.callstatusLoader

    QtObject {
        id: obj_Information

        property AssessmentList assessmentList: AssessmentList{}
        property AssessmentLoader assessmentLoader: AssessmentLoader {
            onNewInfo: { assessmentList.create( info ) }
        }

        property AssessmenttypeList assessmenttypeList: AssessmenttypeList{}
        property AssessmenttypeLoader assessmenttypeLoader: AssessmenttypeLoader {
            onNewInfo: { assessmenttypeList.create( info ) }
        }

        property CallstatusList callstatusList: CallstatusList{}
        property CallstatusLoader callstatusLoader: CallstatusLoader{
            onNewInfo: { callstatusList.create( info ) }
        }
    }
}
