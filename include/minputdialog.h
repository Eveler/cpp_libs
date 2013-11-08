#ifndef MINPUTDIALOG_H
#define MINPUTDIALOG_H

#include <QDialog>

#include "export/mwidgets_export_lib.h"


namespace Ui {
  class MInputDialog;
}

class EXPORT_MWIDGETS MInputDialog : public QDialog
{
    Q_OBJECT


  public:
    explicit MInputDialog(QWidget *parent = 0);
    ~MInputDialog();

    void setLabel( const QString &label );
    QString label() const;

    void setComboBoxItems( const QStringList &items );
    QStringList comboBoxItems() const;

    void setInputText( const QString &text );
    QString inputText() const;

    void setComboBoxEditable( bool editable );
    bool isComboBoxEditable() const;

    static QString getItem( QWidget *parent, const QString &title,
                            const QString &label, const QStringList &items,
                            int current = 0, bool editable = false,
                            Qt::WindowFlags flags = 0 );


  private:
    Ui::MInputDialog *ui;


  private slots:
    void on_comboBox_currentIndexChanged(int index);
};

#endif // MINPUTDIALOG_H
