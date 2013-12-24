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
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)


  public:
    AssessmentLoader(QObject *parent = 0);
    ~AssessmentLoader();

    const QString & lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );

    int count() const;

    Q_INVOKABLE AssessmentInfo * newInfo();


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void countChanged();


  public slots:


  private:
    AssessmentLoader_P *p;
    QEventLoop *loop;


  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(AssessmentLoader)

#endif // ASSESSMENTLOADER_H
