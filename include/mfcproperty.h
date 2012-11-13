#ifndef MFCPROPERTY_H
#define MFCPROPERTY_H

#include <QString>
#include <QVariant>

class MFCProperty
{
public:
  MFCProperty( QString p_Name, QVariant p_Value = QVariant() );
  ~MFCProperty();

  bool isNull() const;

  void setValue( QVariant p_Value = QVariant() );

  const QString & name() const;
  const QVariant & value() const;

private:
  QString *m_Name;
  QVariant *m_Value;
};

#endif // MFCPROPERTY_H
