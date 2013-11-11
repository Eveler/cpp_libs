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
    enum ItemView { ComboBoxView = 0, ListView };
    explicit MInputDialog(QWidget *parent = 0);
    ~MInputDialog();

    void setLabel( const QString &label );
    QString label() const;

    void setItemView( ItemView itemView );
    MInputDialog::ItemView itemView() const;

    void setComboBoxItems( const QStringList &items );
    QStringList comboBoxItems() const;

    void setInputText( const QString &text );
    QStringList inputText() const;

    void setComboBoxEditable( bool editable );
    bool isComboBoxEditable() const;

    static QString getItem( QWidget *parent, const QString &title,
                            const QString &label, const QStringList &items,
                            int current = 0, bool editable = false,
                            Qt::WindowFlags flags = 0 );

    static QStringList getItems( QWidget *parent, const QString &title,
                                 const QString &label, const QStringList &items,
                                 Qt::WindowFlags flags = 0 );


  private:
    Ui::MInputDialog *ui;

    ItemView m__ItemView;


  private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_tBt_SelectAll_clicked();
    void on_tBt_DeselectAll_clicked();
};

#endif // MINPUTDIALOG_H
