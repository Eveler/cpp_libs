#ifndef CLIENTPRIVATESYSTEM_H
#define CLIENTPRIVATESYSTEM_H


class AssessmentLoader;
class AssessmenttypeLoader;
class CallstatusLoader;
class ClientLoader;
class DeclarLoader;
class DeclarClientLoader;
class DepartmentLoader;
class DoctypeLoader;
class HumanLoader;
class OrganisationLoader;
class ProcedureLoader;
class RecipientLoader;
class ResultLoader;
class ResultwayLoader;
class ServiceLoader;
class TrusteeLoader;
class UserLoader;

class ClientPrivateSystem
{
  public:
    static ClientPrivateSystem * instace();

    void setAssessmentLoader( AssessmentLoader *loader );
    AssessmentLoader * assessmentLoader() const;

    void setAssessmenttypeLoader( AssessmenttypeLoader *loader );
    AssessmenttypeLoader * assessmenttypeLoader() const;

    void setCallstatusLoader( CallstatusLoader *loader );
    CallstatusLoader * callStatusLoader() const;

    void setDeclarLoader( DeclarLoader *loader );
    DeclarLoader * declarLoader() const;

    void setClientLoader( ClientLoader *loader );
    ClientLoader * clientLoader() const;

    void setDeclarClientLoader( DeclarClientLoader *loader );
    DeclarClientLoader * declarClientLoader() const;

    void setDepartmentLoader( DepartmentLoader *loader );
    DepartmentLoader * departmentLoader() const;

    void setDoctypeLoader( DoctypeLoader *loader );
    DoctypeLoader * doctypeLoader() const;

    void setHumanLoader( HumanLoader *loader );
    HumanLoader * humanLoader() const;

    void setOrganisationLoader( OrganisationLoader *loader );
    OrganisationLoader * organisationLoader() const;

    void setProcedureLoader( ProcedureLoader *loader );
    ProcedureLoader * procedureLoader() const;

    void setRecipientLoader( RecipientLoader *loader );
    RecipientLoader * recipientLoader() const;

    void setResultLoader( ResultLoader *loader );
    ResultLoader * resultLoader() const;

    void setResultwayLoader( ResultwayLoader *loader );
    ResultwayLoader * resultwayLoader() const;

    void setServiceLoader( ServiceLoader *loader );
    ServiceLoader * serviceLoader() const;

    void setTrusteeLoader( TrusteeLoader *loader );
    TrusteeLoader * trusteeLoader() const;

    void setUserLoader( UserLoader *loader );
    UserLoader * userLoader() const;


  private:
    static ClientPrivateSystem *m__Instance;
    AssessmentLoader *m__AssessmentLoader;
    AssessmenttypeLoader *m__AssessmenttypeLoader;
    CallstatusLoader *m__CallStatusLoader;
    ClientLoader *m__ClientLoader;
    DeclarLoader *m__DeclarLoader;
    DeclarClientLoader *m__DeclarClientLoader;
    DepartmentLoader *m__DepartmentLoader;
    DoctypeLoader *m__DoctypeLoader;
    HumanLoader *m__HumanLoader;
    OrganisationLoader *m__OrganisationLoader;
    ProcedureLoader *m__ProcedureLoader;
    RecipientLoader *m__RecipientLoader;
    ResultLoader *m__ResultLoader;
    ResultwayLoader *m__ResultwayLoader;
    ServiceLoader *m__ServiceLoader;
    TrusteeLoader *m__TrusteeLoader;
    UserLoader *m__UserLoader;

    ClientPrivateSystem();
};

#endif // CLIENTPRIVATESYSTEM_H
