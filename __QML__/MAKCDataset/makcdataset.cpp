#include "makcdataset.h"


MDoctypeDataSource *m__DoctypeDataSource = NULL;
MDocumentDataSource *m__DocumentDataSource = NULL;
MHumanDataSource *m__HumanDataSource = NULL;
MOrganizationDataSource *m__OrgDataSource = NULL;
MProcedureDataSource *m__ProcedureDataSource = NULL;
MRecipientDataSource *m__RecipientDataSource = NULL;
MDepartmentDataSource *m__DepartmentDataSource = NULL;
MDirectionDataSource *m__DirectionDataSource = NULL;
MUserDataSource *m__UserDataSource = NULL;

void MAKCDataset::initializeMAKC( QObject *parent )
{
  m__DoctypeDataSource = new MDoctypeDataSource( parent );
  m__DocumentDataSource = new MDocumentDataSource( parent );
  m__HumanDataSource = new MHumanDataSource( parent );
  m__OrgDataSource = new MOrganizationDataSource( parent );
  m__ProcedureDataSource = new MProcedureDataSource( parent );
  m__RecipientDataSource = new MRecipientDataSource( parent );
  m__DepartmentDataSource = new MDepartmentDataSource( parent );
  m__DirectionDataSource = new MDirectionDataSource( parent );
  m__UserDataSource = new MUserDataSource( parent );
}

MDoctypeDataSource * MAKCDataset::MAKC_DoctypeDataSource()
{
  return m__DoctypeDataSource;
}

MDocumentDataSource * MAKCDataset::MAKC_DocumentDataSource()
{
  return m__DocumentDataSource;
}

MHumanDataSource * MAKCDataset::MAKC_HumanDataSource()
{
  return m__HumanDataSource;
}

MOrganizationDataSource * MAKCDataset::MAKC_OrgDataSource()
{
  return m__OrgDataSource;
}

MProcedureDataSource * MAKCDataset::MAKC_ProcedureDataSource()
{
  return m__ProcedureDataSource;
}

MRecipientDataSource * MAKCDataset::MAKC_RecipientDataSource()
{
  return m__RecipientDataSource;
}

MDepartmentDataSource * MAKCDataset::MAKC_DepartmentDataSource()
{
  return m__DepartmentDataSource;
}

MDirectionDataSource * MAKCDataset::MAKC_DirectionDataSource()
{
  return m__DirectionDataSource;
}

MUserDataSource * MAKCDataset::MAKC_UserDataSource()
{
  return m__UserDataSource;
}
