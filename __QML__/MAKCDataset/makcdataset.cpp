#include "makcdataset.h"


MDatabase *m__Database = NULL;
MDoctypeDataSource *m__DoctypeDataSource = NULL;
MDocumentDataSource *m__DocumentDataSource = NULL;
MHumanDataSource *m__ClientDataSource = NULL;
MHumanDataSource *m__OrgDataSource = NULL;

void MAKCDataset::initializeMAKC( QObject *parent )
{
  m__Database = new MDatabase;
  m__DoctypeDataSource = new MDoctypeDataSource( parent );
  m__DocumentDataSource = new MDocumentDataSource( parent );
  m__ClientDataSource = new MHumanDataSource( parent );
  m__OrgDataSource = new MHumanDataSource( parent );
}

MDatabase * MAKCDataset::MAKC_Database()
{
  return m__Database;
}

MDoctypeDataSource * MAKCDataset::MAKC_DoctypeDataSource()
{
  return m__DoctypeDataSource;
}

MDocumentDataSource * MAKCDataset::MAKC_DocumentDataSource()
{
  return m__DocumentDataSource;
}

MHumanDataSource * MAKCDataset::MAKC_ClientDataSource()
{
  return m__ClientDataSource;
}

MHumanDataSource * MAKCDataset::MAKC_OrgDataSource()
{
  return m__OrgDataSource;
}
