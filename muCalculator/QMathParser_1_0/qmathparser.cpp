#include "qmathparser.h"
#include "ui_qmathparser.h"
#include "muParser/muParser.h"
#include <QtWidgets>
#include <QCoreApplication>

QMathParser::QMathParser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QMathParser)
{
    ui->setupUi(this);
    this->keyGroup();
    connect(ui->textEdit,SIGNAL(textChanged(QString)),this,SLOT(parse()));
    connect(ui->actionExit,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->actionHelp,SIGNAL(triggered()),this,SLOT(help()));
}

QMathParser::~QMathParser()
{
    delete ui;
}

void QMathParser::keyGroup()
{
        keys = new QButtonGroup;
        keys->addButton(ui->pushButton_1);
        keys->addButton(ui->pushButton_2);
        keys->addButton(ui->pushButton_11);
        keys->addButton(ui->pushButton_12);
        keys->addButton(ui->pushButton_13);
        keys->addButton(ui->pushButton_14);
        keys->addButton(ui->pushButton_15);
        keys->addButton(ui->pushButton_16);
        keys->addButton(ui->pushButton_17);
        keys->addButton(ui->pushButton_18);
        keys->addButton(ui->pushButton_19);
        keys->addButton(ui->pushButton_20);
        keys->addButton(ui->pushButton_21);
        keys->addButton(ui->pushButton_22);
        keys->addButton(ui->pushButton_23);
        keys->addButton(ui->pushButton_24);
        keys->addButton(ui->pushButton_25);
        keys->addButton(ui->pushButton_26);
        keys->addButton(ui->pushButton_27);
        keys->addButton(ui->pushButton_28);
        keys->addButton(ui->pushButton_29);
        keys->addButton(ui->pushButton_30);
        keys->addButton(ui->pushButton_31);
        keys->addButton(ui->pushButton_32);
        keys->addButton(ui->pushButton_33);
        keys->addButton(ui->pushButton_34);
        keys->addButton(ui->pushButton_35);
        keys->addButton(ui->pushButton_36);
        keys->addButton(ui->pushButton_37);
        keys->addButton(ui->pushButton_38);
        keys->addButton(ui->pushButton_39);
        keys->addButton(ui->pushButton_40);
        keys->addButton(ui->pushButton_41);
        keys->addButton(ui->pushButton_42);
        keys->addButton(ui->pushButton_43);
        keys->addButton(ui->pushButton_44);
        keys->addButton(ui->pushButton_45);
        keys->addButton(ui->pushButton_46);
        keys->addButton(ui->pushButton_47);
        keys->addButton(ui->pushButton_48);
        keys->addButton(ui->pushButton_49);
        keys->addButton(ui->pushButton_50);
        keys->addButton(ui->pushButton_51);
        keys->addButton(ui->pushButton_52);
        keys->addButton(ui->pushButton_53);
        keys->addButton(ui->pushButton_54);
        keys->addButton(ui->pushButton_55);
        keys->addButton(ui->pushButton_56);
        connect(keys,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(insertkey(QAbstractButton*)));
}

void QMathParser::insertkey(QAbstractButton *btn)
{
    if (btn->objectName()=="pushButton_11" or btn->objectName()=="pushButton_12" or btn->objectName()=="pushButton_13" or btn->objectName()=="pushButton_14" or btn->objectName()=="pushButton_15" or btn->objectName()=="pushButton_16" or btn->objectName()=="pushButton_17" or btn->objectName()=="pushButton_18" or btn->objectName()=="pushButton_19" or btn->objectName()=="pushButton_20" or btn->objectName()=="pushButton_21" or btn->objectName()=="pushButton_22" or btn->objectName()=="pushButton_23" or btn->objectName()=="pushButton_24" or btn->objectName()=="pushButton_25" or btn->objectName()=="pushButton_26" or btn->objectName()=="pushButton_27" or btn->objectName()=="pushButton_28" or btn->objectName()=="pushButton_29" or btn->objectName()=="pushButton_30" or btn->objectName()=="pushButton_31" or btn->objectName()=="pushButton_32" or btn->objectName()=="pushButton_33" or btn->objectName()=="pushButton_34"){
        ui->textEdit->insert(btn->text().append("()"));
        ui->textEdit->setFocus();
        ui->textEdit->cursorBackward(false,1);}
    else
    {
        ui->textEdit->insert(btn->text());
        ui->textEdit->setFocus();}
}

void QMathParser::parse()
{
    expression = ui->textEdit->text();
    mu::string_type expression_buffer;
    QByteArray expression_array = expression.toLocal8Bit();
    char *expression_chars = expression_array.data();
    expression_buffer = expression_chars;
    try
    {
    p.SetExpr(expression_buffer);
    result = p.Eval();
    char buffer[expression_array.size()+1];
    sprintf(buffer,"%f",result);
    result_buffer = buffer;
    }
    catch(mu::Parser::exception_type &e)
    {
    result_buffer = "error";
    }
    ui->lcdres->setDigitCount(result_buffer.length());
    ui->lcdres->display(result_buffer);
}

void QMathParser::about()
{
        QDialog *Dialog = new QDialog(this);
        QGridLayout *gridLayout;
        QDialogButtonBox *buttonBox;
        QLabel *label;
        QGroupBox *groupBox;
        QGridLayout *gridLayout_2;
        QLabel *label_2;
        QLabel *label_3;

        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(Dialog);

        Dialog->setWindowTitle(tr("Dialog", "About"));
             label->setText(tr("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
     "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
     "p, li { white-space: pre-wrap; }\n"
     "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
     "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:600;\">QMathParser</span></p>\n"
     "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">version 1.0</span></p>\n"
     "<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
     "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px;"
                             " margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Copyright \302\251 2010 Muhammad Umar</span></p>\n"
     "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"http://qmathparser.sf.net/\"><span style=\" font-size:8pt; text-decoration: underline; color:#0000ff;\">qmathparser.sf.net</span></a></p></body></html>"));
             groupBox->setTitle(tr("Dialog"));
             label_2->setText(tr("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
     "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
     "p, li { white-space: pre-wrap; }\n"
     "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
     "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">muParser v1.34</span><span style=\" font-size:10pt;\"> (a fast math expression parser)</span></p>\n"
     "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Copyright \302\251 2004-2010 Ingo Berg</span></p>\n"
     "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"http://muparser.sourceforge.net/\"><span style=\" font-size:8pt; text"
                             "-decoration: underline; color:#0000ff;\">muparser.sourceforge.net</span></a></p></body></html>"));
             label_3->setText(tr("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
     "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
     "p, li { white-space: pre-wrap; }\n"
     "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
     "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Qt Framework v4.6.3</span><span style=\" font-size:10pt;\"> (a C++ toolkit)</span></p>\n"
     "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Copyright \302\251 2010 Nokia Corporation</span></p>\n"
     "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"http://qt.nokia.com/\"><span style=\" font-size:8pt; text-decoration: underli"
                             "ne; color:#0000ff;\">qt.nokia.com</span></a></p></body></html>"));

             Dialog->exec();

}

void QMathParser::help()
{
        QDialog *Dialog = new QDialog(this);
        QGridLayout *gridLayout;
        QDialogButtonBox *buttonBox;
        QTextBrowser *textBrowser;

        if (Dialog->objectName().isEmpty())
                Dialog->setObjectName(QString::fromUtf8("Dialog"));
            Dialog->resize(500, 400);
            gridLayout = new QGridLayout(Dialog);
            gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
            buttonBox = new QDialogButtonBox(Dialog);
            buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
            buttonBox->setOrientation(Qt::Horizontal);
            buttonBox->setStandardButtons(QDialogButtonBox::Close);

            gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

            textBrowser = new QTextBrowser(Dialog);
            textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

            gridLayout->addWidget(textBrowser, 1, 0, 1, 1);

            QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
            QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

            QMetaObject::connectSlotsByName(Dialog);

            textBrowser->setSource(QUrl("qrc:/qmp/resource/help.html"));

            Dialog->exec();
}
