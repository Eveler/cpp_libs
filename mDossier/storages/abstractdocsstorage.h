#ifndef ABSTRACTDOCSSTORAGE_H
#define ABSTRACTDOCSSTORAGE_H

#include <QObject>
#include <QHash>
#include <QPair>
#include <QDebug>
#include "mfcdocument.h"

/** \brief \class AbstractDocsStorage - ������� ����� ��� ���������� ����������
�������� ���������� �� ������� ������� (�������). ������������� �� �������
Singleton.
  ��� ��������� ������ �� ��������� ������ ������ \a addStorage. ��� ��������
\a removeStorage
*/
class AbstractDocsStorage : public QObject
{
  Q_OBJECT

protected:
  Q_INVOKABLE explicit AbstractDocsStorage(const QString storageName="__default_storage",
                               QObject *parent = 0);
  virtual ~AbstractDocsStorage();
  static bool registerStorage(const QString storageName,QObject* instance);
  void setError(const QString str);
  static QString errStr;
  bool connected;

public:
  /** ������, ���� ����������, � ���������� ������ �� ��������� ������,
��������������� � \arg storageName, ���������� ������� ������ �� ���������
������
*/
  static AbstractDocsStorage& addStorage(
      const QString storageName="__default_storage");
  static void removeStorage(const QString storageName);
  virtual void removeStorage();
  static QStringList storagesNames();
  static bool contains(const QString storageName);
  int references();
  /** ������������� ���������� � �������� �������� \arg host �� �����
������������ \arg user �� ������ \arg pass �� ����� \arg port
*/
  virtual bool connectToHost(const QString user,const QString pass,
                             const QString host,const quint16 port=0)=0;
  virtual int port() const=0;
  static QString errorString();

private:
  static QHash< QString,QPair< AbstractDocsStorage*,int > > instances;
  QString instanceName;

signals:
  void progressRangeChanged(int minimum,int maximum);
  void progressTextChanged(QString progressText);
  void progressValueChanged(int progressValue);
  void dataTransferProgress(qint64 done,qint64 total,MFCDocument* doc);
  void done(bool);
  void error(QString);
  void saved(QString);
  void loaded(MFCDocument*);

public slots:
  virtual bool save(MFCDocument* doc,QString declarNumber=QString())=0;
  virtual bool load(QString documentUrl,MFCDocument*)=0;
  virtual void cancel()=0;

};

#endif // ABSTRACTDOCSSTORAGE_H
