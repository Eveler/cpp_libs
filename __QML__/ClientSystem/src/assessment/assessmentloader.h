#ifndef ASSESSMENTLOADER_H
#define ASSESSMENTLOADER_H

#include <QObject>

#include <QtQml>


class AssessmentLoader_P;
class AssessmentInfo;

class AssessmentLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AssessmentLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)


  public:
    AssessmentLoader(QObject *parent = 0);
    ~AssessmentLoader();

    const QString & lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( AssessmentInfo *info );


  public slots:


  private:
    AssessmentLoader_P *p;
    QEventLoop *loop;


  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(AssessmentLoader)

#endif // ASSESSMENTLOADER_H
