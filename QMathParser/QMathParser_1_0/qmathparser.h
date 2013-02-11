#ifndef QMATHPARSER_H
#define QMATHPARSER_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QButtonGroup>
#include "muParser/muParser.h"

namespace Ui {
    class QMathParser;
}

class QMathParser : public QMainWindow
{
    Q_OBJECT

public:
    explicit QMathParser(QWidget *parent = 0);
    ~QMathParser();

private:
    Ui::QMathParser *ui;
    QButtonGroup *keys;
    void keyGroup();

    mu::Parser p;
    double result;
    QString result_buffer;
    QString expression;

private slots:
    void insertkey(QAbstractButton*);
    void parse();
    void about();
    void help();
};

#endif // QMATHPARSER_H
