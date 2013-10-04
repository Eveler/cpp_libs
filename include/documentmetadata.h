#ifndef DOCUMENTMETADATA_H
#define DOCUMENTMETADATA_H

#include <QDialog>
#include "export/docwidgets_export.h"
#include "mfcdocument.h"

namespace Ui {
class DocumentMetadata;
}

class DOCWIDGETSSHARED_EXPORT DocumentMetadata : public QDialog
{
  Q_OBJECT

public:
  explicit DocumentMetadata(MFCDocument *doc,QWidget *parent = 0);
  ~DocumentMetadata();

  void setCancelEnabled(bool enabled=true);
  void setAcceptEnabled(bool enabled=true);

public slots:
  void setOriginalPages(int p);
  void setCopyPages(int p);

private slots:
  void on_spBox_OriginalNumber_valueChanged(int arg1);

  void on_spBox_CopyNumber_valueChanged(int arg1);

  void on_gBox_Original_toggled(bool arg1);

  void on_gBox_Copy_toggled(bool arg1);

  bool canAccept() const;
  void on_buttonBox_accepted();

  void on_spBox_OriginalPages_valueChanged(int arg1);

  void on_spBox_CopyPages_valueChanged(int arg1);

private:
  Ui::DocumentMetadata *ui;
  MFCDocument *document;
  int original_pages;
  int copy_pages;
  int original_number;
  int copy_number;
};

#endif // DOCUMENTMETADATA_H
