#ifndef MLOGINDIALOG_H
#define MLOGINDIALOG_H

#include <QDialog>

#include "export/mwidgets_export_lib.h"


namespace Ui {
class MLoginDialog;
}

class MLoginDialog_P;

class EXPORT_MWIDGETS MLoginDialog : public QDialog
{
  Q_OBJECT
  friend class MLoginDialog_P;


public:
  explicit MLoginDialog(QWidget *parent = 0);
  ~MLoginDialog();

  void setNames( const QStringList &names );
  const QStringList & names() const;

  void setNameEditable( bool editable );
  bool isNameEditable() const;

  QString selectedName() const;
  QString selectedPassword() const;


private:
  Ui::MLoginDialog *ui;

  MLoginDialog_P *p;
};

#endif // MLOGINDIALOG_H
