#ifndef MAKCDATASET_H
#define MAKCDATASET_H

#include <QObject>

#include "mdatabase.h"

#include "mdoctypedatasource.h"
#include "mdoctypedbwrapper.h"

#include "mdocumentdatasource.h"
#include "mdocumentdbwrapper.h"

#include "mhumandatasource.h"
#include "mhumandbwrapper.h"

#include "morganizationdatasource.h"
#include "morganizationdbwrapper.h"

#include "mproceduredatasource.h"
#include "mproceduredbwrapper.h"

#include "mrecipientdatasource.h"
#include "mrecipientdbwrapper.h"

#include "mdepartmentdatasource.h"
#include "mdepartmentdbwrapper.h"

#include "mdirectiondatasource.h"
#include "mdirectiondbwrapper.h"

#include "muserdatasource.h"
#include "muserdbwrapper.h"


namespace MAKCDataset {
  void initializeMAKC( QObject * parent = NULL );
  MDoctypeDataSource * MAKC_DoctypeDataSource();
  MDocumentDataSource * MAKC_DocumentDataSource();
  MHumanDataSource * MAKC_HumanDataSource();
  MOrganizationDataSource * MAKC_OrgDataSource();
  MProcedureDataSource * MAKC_ProcedureDataSource();
  MRecipientDataSource * MAKC_RecipientDataSource();
  MDepartmentDataSource * MAKC_DepartmentDataSource();
  MDirectionDataSource * MAKC_DirectionDataSource();
  MUserDataSource * MAKC_UserDataSource();
}

#endif // MAKCDATASET_H
