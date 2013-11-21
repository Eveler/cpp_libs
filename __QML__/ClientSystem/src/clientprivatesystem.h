#ifndef CLIENTPRIVATESYSTEM_H
#define CLIENTPRIVATESYSTEM_H


class CallstatusLoader;
class DepartmentLoader;
class DoctypeLoader;
class HumanLoader;
class ProcedureLoader;
class RecipientLoader;
class UserLoader;

class ClientPrivateSystem
{
  public:
    static ClientPrivateSystem * instace();

    void setCallstatusLoader( CallstatusLoader *loader );
    CallstatusLoader * callStatusLoader() const;

    void setDepartmentLoader( DepartmentLoader *loader );
    DepartmentLoader * departmentLoader() const;

    void setDoctypeLoader( DoctypeLoader *loader );
    DoctypeLoader * doctypeLoader() const;

    void setHumanLoader( HumanLoader *loader );
    HumanLoader * humanLoader() const;

    void setProcedureLoader( ProcedureLoader *loader );
    ProcedureLoader * procedureLoader() const;

    void setRecipientLoader( RecipientLoader *loader );
    RecipientLoader * recipientLoader() const;

    void setUserLoader( UserLoader *loader );
    UserLoader * userLoader() const;


  private:
    static ClientPrivateSystem *m__Instance;
    CallstatusLoader *m__CallStatusLoader;
    DepartmentLoader *m__DepartmentLoader;
    DoctypeLoader *m__DoctypeLoader;
    HumanLoader *m__HumanLoader;
    ProcedureLoader *m__ProcedureLoader;
    RecipientLoader *m__RecipientLoader;
    UserLoader *m__UserLoader;

    ClientPrivateSystem();
};

#endif // CLIENTPRIVATESYSTEM_H
