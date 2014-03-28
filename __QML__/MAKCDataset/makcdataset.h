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
#include "morganizationdbwrapper.h"


namespace MAKCDataset {
  void initializeMAKC( QObject * parent = NULL );
  MDatabase * MAKC_Database();
  MDoctypeDataSource * MAKC_DoctypeDataSource();
  MDocumentDataSource * MAKC_DocumentDataSource();
  MHumanDataSource * MAKC_HumanDataSource();
  MHumanDataSource * MAKC_OrgDataSource();
}

#endif // MAKCDATASET_H
