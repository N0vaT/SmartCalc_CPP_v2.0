#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <creditcalc.h>

#include <QMainWindow>
#include <QVector>
// #include <depositcalc.h>

#ifdef __controllers
#endif
#include "../controllers/CalcController.h"
#ifdef __controllers
#endif

#ifdef __model
#endif
#include "../model/Calculator.h"
#include "../model/CreditCalculator.h"
#include "../model/Parser.h"
#include "../model/Validator.h"
#ifdef __model
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::CalcController controller, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  s21::CalcController calcController;
  double xBegin, xEnd, yBegin, yEnd, h, X, Y;
  QVector<double> x, y;
  int N;

 private slots:
  void digits_numbers();

 private slots:
  void del_line();

 private slots:
  void functions();

 private slots:
  void calculate();

 private slots:
  void add_graphic();

  void on_bCredit_clicked();
  // void on_bDeposit_clicked();
};
#endif  // MAINWINDOW_H
