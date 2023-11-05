#include "mainwindow.h"

#include <cstring>

#include "ui_mainwindow.h"

MainWindow::MainWindow(const s21::CalcController controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), calcController(controller) {
  ui->setupUi(this);

  connect(ui->b_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bAdd, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bSub, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bMul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bDiv, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bPow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bMod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bPoint, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_bracket_on, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_bracket_off, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->b_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->b_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->b_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->b_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->b_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->b_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->b_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->b_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->b_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->bEqual, SIGNAL(clicked()), this, SLOT(calculate()));
  connect(ui->lineEdit, SIGNAL(returnPressed()), SLOT(calculate()));
  connect(ui->bDelete, SIGNAL(clicked()), this, SLOT(del_line()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString out_string;
  out_string = (ui->lineEdit->text() + button->text());

  ui->lineEdit->setText(out_string);
}

void MainWindow::del_line() { ui->lineEdit->clear(); }

void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();
  QString out_string;
  out_string = (ui->lineEdit->text() + button->text() + "(");

  ui->lineEdit->setText(out_string);
}

void MainWindow::calculate() {
  ui->label_error->clear();
  QString str = ui->lineEdit->text();
  std::string my_str = str.toStdString();
  try {
    std::string validStr = calcController.validate(my_str);
    std::string postfixStr = calcController.parsing(validStr);
    if (postfixStr.find('x') == -1) {
      QString out_str = QString::number(calcController.calculate(postfixStr));
      ui->lineEdit->setText(out_str);
    } else {
      add_graphic();
    }
  } catch (const std::exception &e) {
    ui->label_error->setText(QString::fromStdString(e.what()));
  }
}

void MainWindow::add_graphic() {
  h = 0.01;
  if (ui->lineEdit_x_begin->text().isEmpty()) {
    ui->lineEdit_x_begin->setText("" + QString::number(-4));
  }
  if (ui->lineEdit_x_end->text().isEmpty()) {
    ui->lineEdit_x_end->setText("" + QString::number(10));
  }
  if (ui->lineEdit_y_begin->text().isEmpty()) {
    ui->lineEdit_y_begin->setText("" + QString::number(-4));
  }
  if (ui->lineEdit_y_end->text().isEmpty()) {
    ui->lineEdit_y_end->setText("" + QString::number(2));
  }
  yBegin = ui->lineEdit_y_begin->text().toDouble();
  xEnd = ui->lineEdit_x_end->text().toDouble();
  xBegin = ui->lineEdit_x_begin->text().toDouble();
  yEnd = ui->lineEdit_y_end->text().toDouble();

  if (xEnd < xBegin || yEnd < yBegin) {
    xBegin = -4;
    xEnd = 10;
    yBegin = -4;
    yEnd = 2;
  }
  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);
  N = (xEnd - xBegin) / h + 1;
  int i = 0;
  QVector<double> x(N), y(N);
  for (X = xBegin; X <= xEnd; X += h) {
    x[i] = X;
    Y = calcController.calculateX(X);
    ;
    if (Y < yEnd && Y > yBegin) {
      y[i] = Y;
    } else {
      y[i] = NAN;
    }
    ++i;
  }
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}

void MainWindow::on_bCredit_clicked() {
  CreditCalc *credit = new CreditCalc(calcController);
  credit->show();
}
