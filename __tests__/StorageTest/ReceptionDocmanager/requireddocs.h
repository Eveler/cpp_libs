#ifndef REQUIREDDOCS_H
#define REQUIREDDOCS_H

#include <QObject>
#include <QUuid>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include "reqdocsmodel.h"

typedef struct DocType{
  QString name;
  QString requirements;
  QString organ;
  QString organ_addr;
  bool operator<(const DocType &other) const{
    return other.name<name && other.requirements<requirements &&
        other.organ<organ && other.organ_addr<organ_addr;
  }
} DocType;

class RequiredDocs : public QObject
{
  Q_OBJECT
public:
  explicit RequiredDocs(QSqlDatabase db,QObject *parent=0);
  explicit RequiredDocs(QVariant serviceID, QSqlDatabase db,
                        QString se_alias=QString() ,QObject *parent = 0);
  ~RequiredDocs();
  bool addRequiredDoc(const QVariant &type, const bool required=true,
                      const int amount=1, const QVariant &category=QVariant(),
                      const QVariant &requirements=QVariant(),
                      const QVariant &organ=QVariant(),
                      const QVariant &organ_addr=QVariant(), int priority=0);
  bool setRequiredDocAmount(const QVariant &type,const int amount);
  bool setDocTypeRequired(const QVariant &type,const bool required=true);
  void useDocType(const QVariant &type);
  void useDocIndex(const QModelIndex &index);
  bool removeRequiredDoc(const QVariant &type);
  QAbstractItemModel *model() const;
  QVariantList requiredDocTypes() const;
  QVariantList allDocTypes() const;
  int requiredDocAmount(const QVariant &type) const;
  int remainDocAmount(const QVariant &type) const;
  QString errorString() const;
  QVariant serviceID() const;

private:
  ReqDocsModel *mdl;
//  QStandardItemModel *int_mdl;
  QString errStr;
  QUuid instanceName;
  QSqlDatabase m_DB;
  QVariant srv_id;
  QMap< DocType*,QString > categories;

  void init();

signals:
  void error(QString);

public slots:
  void reset();

private slots:
  void setError(const QString &str);
};

#endif // REQUIREDDOCS_H
