QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    creditcalc.cpp \
    ../model/Calculator.cc \
    ../model/Parser.cc \ 
    ../model/Validator.cc \
    ../model/CreditCalculator.cc \
    ../controllers/CalcController.cc

HEADERS += \
    mainwindow.h \
    qcustomplot.h \
    creditcalc.h \
    ../model/Calculator.h \
    ../model/Parser.h \ 
    ../model/Validator.h \
    ../model/CreditCalculator.h \
    ../controllers/CalcController.h

FORMS += \
    mainwindow.ui \
    creditcalc.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
