#ifndef MFCRECORD_H
#define MFCRECORD_H

#include <QObject>
#include <QStringList>
#include <QUuid>

#include "propertiesview.h"
#include "mfcproperty.h"

class MFCRecord: public QObject
{
  Q_OBJECT
public:
  static QString unionValues( const QStringList &keyWords, MFCRecord *record );
  static QString unionValuesShortDate( const QStringList &keyWords, MFCRecord *record );

  explicit MFCRecord( PropertiesLink *pLink );
  ~MFCRecord();

  bool addParentRecord( MFCRecord *parent );
  bool removeParentRecord( MFCRecord *parent );
  const QList<MFCRecord *> & parentRecords() const;
  bool addChildRecord( MFCRecord *child );
  bool replaceChildRecord( MFCRecord *old_child, MFCRecord *new_child );
  bool removeChildRecord( MFCRecord *child );
  const QList<MFCRecord *> & childrenRecord() const;

  PropertiesLink * propertiesLink() const;
  PropertiesView * propertiesView() const;
  Properties * properties() const;

  bool setDefaultProperty( const QString &p_Name, QVariant p_Value );
  bool setProperty( const QString &p_Name, QVariant p_Value );

  const QVariant & defaultProperty( const QString &p_Name ) const;
  const QVariant & currentProperty( const QString &p_Name ) const;

  QStringList changedProperties();

//  MFCRecord *findChildByName( const QString &name );
  MFCRecord *findChildByName( const QString &propertiesView_Alias ) const;

//  bool setDefaultValue( Properties *properties, const QString &p_Name, QVariant p_Value );
//  bool setCurrentValue( Properties *properties, const QString &p_Name, QVariant p_Value );
//  QVariant getDefaultValue( Properties *properties, const QString &p_Name );
//  QVariant getCurrentValue( Properties *properties, const QString &p_Name );
  bool setDefaultValue( PropertiesView *pv, const QString &p_Name, QVariant p_Value );
  bool setCurrentValue( PropertiesView *pv, const QString &p_Name, QVariant p_Value );
  QVariant getDefaultValue( PropertiesView *pv, const QString &p_Name );
  QVariant getCurrentValue( PropertiesView *pv, const QString &p_Name );

//  MFCRecord * getRecordByProperty( Properties *properties );
  MFCRecord * getRecordByPropertiesView( PropertiesView *pv_Child,
                                         PropertiesView *pv_Parent = NULL,
                                         QString keyField = QString() );
  QList<MFCRecord *> getRootRecords( PropertiesView *pv );
//  MFCRecord * findRecord( Properties *properties, const QString &p_Name, QVariant p_Value );
  MFCRecord * findRecord( PropertiesView *pv, const QString &p_Name, QVariant p_Value );

  MFCRecord * copy( PropertiesLink *pLink );
  bool copy( MFCRecord *other );

  void dataRecovery();
  void dataSync();

  const QUuid & uuid() const;

  bool operator ==( const MFCRecord &other ) const;
  bool isSame( const MFCRecord &other, const QStringList &propertyNames ) const;

  void requestEdit();

  QStringList keyFieldForChild(MFCRecord *child) const;

signals:
  void propertyChanged( const QString &p_Name, QVariant p_OldValue, QVariant p_NewValue );
  void propertyChanged( const QString &p_Name, QVariant p_Value );
  void propertyChanged( const QString &p_Name );
  void childAdded( MFCRecord *record );
  void childReplaced( MFCRecord *old_record, MFCRecord *new_record );
  void childRemoved( MFCRecord *record );
  void dataReversed();
  void recordDestroyed( QUuid uuid );
  void editRequested();

public slots:
  bool setCurrentProperty( const QString &p_Name, QVariant p_Value );

private:
  PropertiesLink *m_PropertiesLink;
  PropertiesView *m_PropertiesView;
  Properties *m_Properties;

  QList<MFCRecord *> m_Parents;
  QList<MFCRecord *> m_Children;

  QList<MFCProperty *> m_DefaultProperties;

  QList<MFCProperty *> m_CurrentProperties;

  static QList<QVariant::Type> integerTypes;

  QVariant m_NULL;

  bool blockPropertyChanged;
  bool blockOnChangeChild;

  QUuid m_Uuid;

  void setParent( QObject *obj );

  QObject * parent();
  QList<QObject *> children();

  bool setProperty( QList<MFCProperty *> & m_MFCProperties,
                    const QString &p_Name, QVariant p_Value );

  const QVariant & property( const QList<MFCProperty *> & m_MFCProperties, const QString &p_Name ) const;

//  MFCRecord * recordByProperty( MFCRecord *record, Properties *properties );
private slots:
  void parentDestroyed( QObject *obj );
  void childDestroyed( QObject *obj );
};

#endif // MFCRECORD_H
