TEMPLATE = app
TARGET = plotter

QT  = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

SOURCES += \
        main.cpp \
        qcustomplot.cpp \
        widget.cpp

HEADERS += \
        qcustomplot.h \
        widget.h

FORMS += \
        widget.ui


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
