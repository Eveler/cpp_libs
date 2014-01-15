pragma Singleton
import QtQuick 2.2

import extensions.mihail.mqmllibraries 1.0
import com.mihail.clientsystem 1.0


Item {
    id: clientSystemSources

    readonly property bool started: obj_Information.queueStarted
    readonly property int progress: ( !obj_Information.currentLoader || obj_Information.currentLoader.count === 0 ?
                                         100 : (obj_Information.currentLoader.receivedCount/obj_Information.currentLoader.count*100.0) )

    readonly property List assessmentList: obj_Information.assessmentList
    readonly property AssessmentLoader assessmentLoader: obj_Information.assessmentLoader

    readonly property List assessmenttypeList: obj_Information.assessmenttypeList
    readonly property AssessmenttypeLoader assessmenttypeLoader: obj_Information.assessmenttypeLoader

    readonly property List callstatusList: obj_Information.callstatusList
    readonly property CallstatusLoader callstatusLoader: obj_Information.callstatusLoader

    readonly property List clientList: obj_Information.clientList
    readonly property ClientLoader clientLoader: obj_Information.clientLoader

    readonly property List declarList: obj_Information.declarList
    readonly property DeclarLoader declarLoader: obj_Information.declarLoader

    readonly property List declarClientList: obj_Information.declarClientList
    readonly property DeclarClientLoader declarClientLoader: obj_Information.declarClientLoader

    readonly property List departmentList: obj_Information.departmentList
    readonly property DepartmentLoader departmentLoader: obj_Information.departmentLoader

    readonly property List doctypeList: obj_Information.doctypeList
    readonly property DoctypeLoader doctypeLoader: obj_Information.doctypeLoader

    readonly property List humanList: obj_Information.humanList
    readonly property HumanLoader humanLoader: obj_Information.humanLoader

    readonly property List organisationList: obj_Information.organisationList
    readonly property OrganisationLoader organisationLoader: obj_Information.organisationLoader

    readonly property List procedureList: obj_Information.procedureList
    readonly property ProcedureLoader procedureLoader: obj_Information.procedureLoader

    readonly property List recipientList: obj_Information.recipientList
    readonly property RecipientLoader recipientLoader: obj_Information.recipientLoader

    readonly property List resultList: obj_Information.resultList
    readonly property ResultLoader resultLoader: obj_Information.resultLoader

    readonly property List resultwayList: obj_Information.resultwayList
    readonly property ResultwayLoader resultwayLoader: obj_Information.resultwayLoader

    readonly property List serviceList: obj_Information.serviceList
    readonly property ServiceLoader serviceLoader: obj_Information.serviceLoader

    readonly property List trusteeList: obj_Information.trusteeList
    readonly property TrusteeLoader trusteeLoader: obj_Information.trusteeLoader

    QtObject {
        id: obj_Information

        property List queue: List{}
        property bool queueStarted: false
        property var currentLoader: null
        //======================================================================

        //======================================================================
        property Component assessment: Component{ Assessment{} }
        property List assessmentList: List{}
        property AssessmentLoader assessmentLoader: AssessmentLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.assessment
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.assessmentList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.assessmentList.specialObjects.length === 0 )
                        {
                            obj_Information.assessmentList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.assessmentList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component assessmenttype: Component{ Assessmenttype{} }
        property List assessmenttypeList: List{}
        property AssessmenttypeLoader assessmenttypeLoader: AssessmenttypeLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.assessmenttype
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.assessmenttypeList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.assessmenttypeList.specialObjects.length === 0 )
                        {
                            obj_Information.assessmenttypeList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.assessmenttypeList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component callstatus: Component{ Callstatus{} }
        property List callstatusList: List{}
        property CallstatusLoader callstatusLoader: CallstatusLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.callstatus
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.callstatusList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.callstatusList.specialObjects.length === 0 )
                        {
                            obj_Information.callstatusList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.callstatusList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component client: Component{ Client{} }
        property List clientList: List{}
        property ClientLoader clientLoader: ClientLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.client
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.clientList, {"identifier": info.identifier(),
                                        "organisationIdentifier": info.organisationIdentifier(),
                                        "humanIdentifier": info.humanIdentifier()} )
                        if ( obj_Information.clientList.specialObjects.length === 0 )
                        {
                            obj_Information.clientList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.clientList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component declar: Component{ Declar{} }
        property List declarList: List{}
        property DeclarLoader declarLoader: DeclarLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.declar
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.declarList, {"identifier": info.identifier(),
                                        "serviceIdentifier": info.serviceIdentifier(),
                                        "number": info.number(),
                                        "createDate": info.createDate(),
                                        "controlDate": info.controlDate(),
                                        "respiteDate": info.respiteDate(),
                                        "closeDate": info.closeDate(),
                                        "firstLandmark": info.firstLandmark(),
                                        "lastLandmark": info.lastLandmark(),
                                        "directionIdentifier": info.directionIdentifier(),
                                        "responsibleIdentifier": info.responsibleIdentifier(),
                                        "ownerIdentifier": info.ownerIdentifier(),
                                        "isnew": info.isnew(),
                                        "deleted": info.deleted(),
                                        "resultIdentifier": info.resultIdentifier(),
                                        "assessmentTypeIdentifier": info.assessmentTypeIdentifier(),
                                        "assessmentIdentifier": info.assessmentIdentifier(),
                                        "resultWayIdentifier": info.resultWayIdentifier(),
                                        "declarClientIdentifiers": info.declarClientIdentifiers(),
                                        "declarTrusteeIdentifiers": info.declarTrusteeIdentifiers()} )
                        if ( obj_Information.declarList.specialObjects.length === 0 )
                        {
                            obj_Information.declarList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.declarList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component declarClient: Component{ DeclarClient{} }
        property List declarClientList: List{}
        property DeclarClientLoader declarClientLoader: DeclarClientLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.declarClient
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.declarClientList, {"identifier": info.identifier(),
                                        "declarIdentifier": info.declarIdentifier(),
                                        "clientIdentifier": info.clientIdentifier()} )
                        if ( obj_Information.declarClientList.specialObjects.length === 0 )
                        {
                            obj_Information.declarClientList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.declarClientList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component department: Component{ Department{} }
        property List departmentList: List{}
        property DepartmentLoader departmentLoader: DepartmentLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.department
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.departmentList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.departmentList.specialObjects.length === 0 )
                        {
                            obj_Information.departmentList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.departmentList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component doctype: Component{ Doctype{} }
        property List doctypeList: List{}
        property DoctypeLoader doctypeLoader: DoctypeLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.doctype
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.doctypeList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.doctypeList.specialObjects.length === 0 )
                        {
                            obj_Information.doctypeList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.doctypeList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component human: Component{ Human{} }
        property List humanList: List{}
        property HumanLoader humanLoader: HumanLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.human
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.humanList, {"identifier": info.identifier(),
                                        "surname": info.surname(),
                                        "firstname": info.firstname(),
                                        "lastname": info.lastname(),
                                        "address": info.address(),
                                        "phone": info.phone(),
                                        "email": info.email()} )
                        if ( obj_Information.humanList.specialObjects.length === 0 )
                        {
                            obj_Information.humanList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.humanList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component organisation: Component{ Organisation{} }
        property List organisationList: List{}
        property OrganisationLoader organisationLoader: OrganisationLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.organisation
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.organisationList, {"identifier": info.identifier(),
                                        "fullname": info.fullname(),
                                        "humanIdentifier": info.humanIdentifier(),
                                        "address": info.address(),
                                        "phone": info.phone(),
                                        "email": info.email()} )
                        if ( obj_Information.organisationList.specialObjects.length === 0 )
                        {
                            obj_Information.organisationList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.organisationList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component procedure: Component{ Procedure{} }
        property List procedureList: List{}
        property ProcedureLoader procedureLoader: ProcedureLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.procedure
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.procedureList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.procedureList.specialObjects.length === 0 )
                        {
                            obj_Information.procedureList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.procedureList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component recipient: Component{ Recipient{} }
        property List recipientList: List{}
        property RecipientLoader recipientLoader: RecipientLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.recipient
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.recipientList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.recipientList.specialObjects.length === 0 )
                        {
                            obj_Information.recipientList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.recipientList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component result: Component{ Result{} }
        property List resultList: List{}
        property ResultLoader resultLoader: ResultLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.result
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.resultList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.resultList.specialObjects.length === 0 )
                        {
                            obj_Information.resultList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.resultList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component resultway: Component{ Resultway{} }
        property List resultwayList: List{}
        property ResultwayLoader resultwayLoader: ResultwayLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.resultway
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.resultwayList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.resultwayList.specialObjects.length === 0 )
                        {
                            obj_Information.resultwayList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.resultwayList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component service: Component{ Service{} }
        property List serviceList: List{}
        property ServiceLoader serviceLoader: ServiceLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.service
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.serviceList, {"identifier": info.identifier(),
                                        "root": info.root(),
                                        "sidx": info.sidx(),
                                        "name": info.name(),
                                        "deadline": info.deadline(),
                                        "workdays": info.workdays(),
                                        "isactive": info.isactive()} )
                        if ( obj_Information.serviceList.specialObjects.length === 0 )
                        {
                            obj_Information.serviceList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.serviceList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component declarTrustee: Component{ DeclarTrustee{} }
        property List trusteeList: List{}
        property TrusteeLoader trusteeLoader: TrusteeLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.declarTrustee
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.trusteeList, {"identifier": info.identifier(),
                                        "declarIdentifier": info.declarIdentifier(),
                                        "trusteeClientIdentifier": info.trusteeClientIdentifier(),
                                        "clientIdentifier": info.clientIdentifier()} )
                        if ( obj_Information.trusteeList.specialObjects.length === 0 )
                        {
                            obj_Information.trusteeList.specialObjects =
                                    MQML.className( curItem )
                        }
                        obj_Information.trusteeList.append( curItem );
                        info.destroy()
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //======================================================================

        //======================================================================
        function loadNext()
        {
            if ( !queueStarted ) return

            if ( obj_Information.queue.length > 0 )
            {
                currentLoader = clientSystemSources.dequeue()
                currentLoader.load()
            }
            else queueStarted = false
        }
    }

    function startQueue()
    {
        obj_Information.queueStarted = true
        obj_Information.loadNext()
    }
    function enqueue( loader )
    {
        obj_Information.queue.append( loader )

//        if ( MQML.className( loader ) ===
//                MQML.className( obj_Information.assessmentLoader ) )
//            obj_Information.queue.append( loader )
//        else if ( MQML.className( loader ) ===
//                 MQML.className( obj_Information.assessmenttypeLoader ) )
//             obj_Information.queue.append( loader )
//        else if ( MQML.className( loader ) ===
//                 MQML.className( obj_Information.callstatusLoader ) )
//             obj_Information.queue.append( loader )
//        else if ( MQML.className( loader ) ===
//                 MQML.className( obj_Information.clientLoader ) )
//             obj_Information.queue.append( loader )
    }
    function dequeue()
    {
        return obj_Information.queue.takeFirst();
    }
}
