#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QWidget>

#include "../controllers/CalcController.h"

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalc(s21::CalcController controller,
                      QWidget *parent = nullptr);
  ~CreditCalc();

 private:
  Ui::CreditCalc *ui;
  s21::CalcController controller;

 private slots:
  void calculate_credit_ann();

 private slots:
  void calculate_credit_dif();
};

#endif  // CREDITCALC_H
