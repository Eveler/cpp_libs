#ifndef MDATEDIALOG_H
#define MDATEDIALOG_H

#include <QDialog>


namespace Ui {
class MDateDialog;
}

class MDateDialog : public QDialog
{
  Q_OBJECT


public:
  explicit MDateDialog(QWidget *parent = 0);
  ~MDateDialog();

  void setDisplayFormat( const QString &displayFormat );
  QString displayFormat() const;

  void setText( const QString &text );
  QString text() const;

  QDateTime dateTime() const;


private:
  Ui::MDateDialog *ui;
};

#endif // MDATEDIALOG_H
