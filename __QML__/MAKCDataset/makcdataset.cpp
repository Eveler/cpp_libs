#include "makcdataset.h"


MDatabase *m__Database = NULL;
MHumanDataSource *m__ClientDataSource = NULL;
MHumanDataSource *m__OrgDataSource = NULL;

void MAKCDataset::initializeMAKC( QObject *parent )
{
  m__Database = new MDatabase;
  m__ClientDataSource = new MHumanDataSource;
  m__OrgDataSource = new MHumanDataSource;
}

MDatabase * MAKCDataset::MAKC_Database()
{
  return m__Database;
}

MHumanDataSource * MAKCDataset::MAKC_ClientDataSource()
{
  return m__ClientDataSource;
}

MHumanDataSource * MAKCDataset::MAKC_OrgDataSource()
{
  return m__OrgDataSource;
}
