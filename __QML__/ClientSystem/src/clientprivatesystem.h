#ifndef CLIENTPRIVATESYSTEM_H
#define CLIENTPRIVATESYSTEM_H


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
class UserLoader;
class ServiceLoader;
class TrusteeLoader;

class ClientPrivateSystem
{
  public:
    static ClientPrivateSystem * instace();

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

    void setUserLoader( UserLoader *loader );
    UserLoader * userLoader() const;

    void setServiceLoader( ServiceLoader *loader );
    ServiceLoader * serviceLoader() const;

    void setTrusteeLoader( TrusteeLoader *loader );
    TrusteeLoader * trusteeLoader() const;


  private:
    static ClientPrivateSystem *m__Instance;
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
    UserLoader *m__UserLoader;
    ServiceLoader *m__ServiceLoader;
    TrusteeLoader *m__TrusteeLoader;

    ClientPrivateSystem();
};

#endif // CLIENTPRIVATESYSTEM_H
