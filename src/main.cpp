#include "view/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Validator validator;
    s21::Parser parser;
    s21::Calculator calculator;
    s21::CreditCalculator credit;
    s21::CalcController controller(validator, parser, calculator, credit);
    MainWindow w(controller);
    w.show();
    return a.exec();
}
