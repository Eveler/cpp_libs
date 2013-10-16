#ifndef REQDOCSMODEL_H
#define REQDOCSMODEL_H

#include <QAbstractItemModel>
#include <QStringList>

class ReqItem
{
public:
  QVariantList data;
  QList< ReqItem* > children;
  ReqItem *parent;
  int priority;
  ~ReqItem(){qDeleteAll(children);}
  bool operator<(const ReqItem &other) const;
  QString type() const;
  void setRequired(bool r=true);
  bool isRequired() const;
  void setAmount(int a);
  int amount() const;
  void use();
  int used() const;
  void setSample(QString s);
  QString sample() const;
  void reset();
};

class ReqDocsModel: public QAbstractItemModel
{
  Q_OBJECT
public:
  ReqDocsModel(QObject *parent=0);
  ~ReqDocsModel();

  bool addDocument(const QString &type, bool required,int amount,
                   const QString &category,const QString &requirements,
                   const QString &organ,const QString &organ_addr,
                   int priority=0);
  bool removeDocument(const QString &type);

  int columnCount(const QModelIndex &parent=QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  int rowCount(const QModelIndex &parent=QModelIndex()) const;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent=QModelIndex()) const;
  QModelIndex parent(const QModelIndex &child) const;
//  bool hasChildren(const QModelIndex &parent) const;

  void useDocType(const QString &type);
  void useDocIndex(const QModelIndex &index);
  QStringList requiredDocTypes() const;
  QStringList allDocTypes() const;
  QStringList categories() const;
  int requiredDocAmount(const QString &type=QString()) const;
  int remainDocAmount(const QString &type=QString()) const;
  bool setAmount(const QString &type, int amount);
  bool setRequired(const QString &type,bool b);
  void reset();

private:
  QStringList headerLabels;
  QList< ReqItem* > items;

  int findDocument(const QString &type,ReqItem *parent=0) const;
  void recalc(ReqItem *parent);
  int visibleRow(ReqItem *item) const;

};

#endif // REQDOCSMODEL_H
