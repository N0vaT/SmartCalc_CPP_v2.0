#include "creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(s21::CalcController controller, QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditCalc), controller(controller) {
  ui->setupUi(this);

  connect(ui->b_ann, SIGNAL(clicked()), this, SLOT(calculate_credit_ann()));
  connect(ui->b_dif, SIGNAL(clicked()), this, SLOT(calculate_credit_dif()));
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::calculate_credit_ann() {
  ui->result_text->clear();
  if (ui->l_sum_credit->text().isEmpty() ||
      ui->l_term_credit->text().isEmpty() || ui->l_percent->text().isEmpty()) {
    ui->result_text->appendPlainText("Введите данные");
  } else {
    double S = ui->l_sum_credit->text().toDouble();
    double N = ui->l_term_credit->text().toDouble();
    double P = ui->l_percent->text().toDouble();
    double paymentByMonth, interestPercent, total;
    std::tie(paymentByMonth, interestPercent, total) =
        controller.calculateCreditAnn(S, N, P);

    ui->result_text->appendPlainText("Ежемесячный платеж - " +
                                     QString::number(paymentByMonth));
    ui->result_text->appendPlainText("Начисленные проценты - " +
                                     QString::number(interestPercent));
    ui->result_text->appendPlainText("Долг + проценты - " +
                                     QString::number(total));
  }
}

void CreditCalc::calculate_credit_dif() {
  ui->result_text->clear();
  if (ui->l_sum_credit->text().isEmpty() ||
      ui->l_term_credit->text().isEmpty() || ui->l_percent->text().isEmpty()) {
    ui->result_text->appendPlainText("Введите данные");
  } else {
    double S = ui->l_sum_credit->text().toDouble();
    double N = ui->l_term_credit->text().toDouble();
    double P = ui->l_percent->text().toDouble() / 100;

    double resProc, resOver;
    std::vector<double> paymentByMonth;
    std::tie(resProc, resOver, paymentByMonth) =
        controller.calculateCreditDif(S, N, P);

    for (int i = 1; i <= N; i++) {
      ui->result_text->appendPlainText("" + QString::number(i) + ". месяц - " +
                                       QString::number(paymentByMonth[i - 1]) +
                                       " руб.");
    }
    ui->result_text->appendPlainText("Начисленные проценты - " +
                                     QString::number(resProc));
    ui->result_text->appendPlainText("Долг + проценты - " +
                                     QString::number(resOver));
  }
}
