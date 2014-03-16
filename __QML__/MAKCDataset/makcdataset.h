#ifndef MAKCDATASET_H
#define MAKCDATASET_H

#include <QObject>

#include "mdatabase.h"
#include "mdocumentdatasource.h"
#include "mdocumentdbwrapper.h"
#include "mhumandatasource.h"
#include "mhumandbwrapper.h"


namespace MAKCDataset {
  void initializeMAKC( QObject * parent = NULL );
  MDatabase * MAKC_Database();
  MHumanDataSource * MAKC_ClientDataSource();
  MHumanDataSource * MAKC_OrgDataSource();
}

#endif // MAKCDATASET_H
