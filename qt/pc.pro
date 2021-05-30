greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pc

SOURCES += src/main.cpp\
        src/mainwindow.cpp

HEADERS  += include/mainwindow.h

FORMS    += mainwindow.ui
