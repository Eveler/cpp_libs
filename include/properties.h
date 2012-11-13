#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QByteArray>
#include <QString>
#include <QVariant>
#include <QHash>
#include <QStringList>
#include <QObject>

class Properties: public QObject
{
  Q_OBJECT
public:
  static Properties * addProperties( const QString &ps_Name );
  static Properties * getProperties( const QString &ps_Name );
  static bool exists( const QString &ps_Name );
  static bool release( const QString &ps_Name );
  static void releaseAll();

  bool isNull();
  const QString & name() const;
  QByteArray hash();

  bool addProperty( const QString &p_Name, QVariant::Type p_Type );
  bool removeProperty( const QString &p_Name );
  void clear();

  bool addPrimaryKey( const QString &p_Name, QVariant::Type p_Type );
  QStringList primaryKey();

  QStringList propertyNames();
  QVariant::Type propertyType( const QString &p_Name ) const;

  bool addChildProperties( Properties *properties );
  bool removeChildProperies( Properties *properties );
  QList<Properties *> childrenProperties() const;

  bool addParentProperties( Properties *properties );
  bool removeParentProperies( Properties *properties );
  QList<Properties *> parentProperties() const;

private:
  static QHash<QString, Properties *> m_Properties;
  static Properties nullProperty;

  QString *m_Name;
  QList<Properties *> m_ParentProperties;
  QList<Properties *> m_ChildrenProperties;

  QList<QString *> m_PropertyNames;
  QHash<QString *, QVariant::Type> m_PropertyTypes;
  QList< QString * > m_PrimaryKey;

  explicit Properties();
  explicit Properties( const QString &ps_Name );
  ~Properties();

//  Q_DISABLE_COPY(Properties)
};

#endif // PROPERTIES_H
