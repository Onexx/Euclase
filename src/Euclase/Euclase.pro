#-------------------------------------------------
#
# Project created by QtCreator 2017-10-31T14:42:37
#
#-------------------------------------------------

QT += core gui printsupport widgets network multimedia multimediawidgets
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Euclase
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        Menu.cpp \
        ReturnButton.cpp \
        data.cpp \
        Navig/DragAndDrop/DropScene.cpp \
        Navig/DragAndDrop/DragCircle.cpp \
        Navig/DragAndDrop/DragRect.cpp \
        Navig/ObservableItems/ObservableRect.cpp \
        Navig/ObservableItems/ObservableCircle.cpp \
        Navig/BarcodePrinter/BarcodePrinter.cpp \
        Navig/BarcodePrinter/Printer.cpp \
        Navig/Navig.cpp \
        MenuInfoPages/InfoView.cpp \
        MenuInfoPages/Partners.cpp \
        MenuInfoPages/Description.cpp \
        MenuInfoPages/Timetable.cpp \
        MenuInfoPages/Instruct.cpp \
    RegistrationForm.cpp

HEADERS += \
        Menu.h \
        ReturnButton.h \
        data.h \
        Statistics/Logs.h \
        Statistics/Statistics.h \
        Navig/DragAndDrop/DropScene.h \
        Navig/DragAndDrop/DragCircle.h \
        Navig/DragAndDrop/DragRect.h \
        Navig/ObservableItems/ObservableRect.h \
        Navig/ObservableItems/ObservableCircle.h \
        Navig/BarcodePrinter/BarcodePrinter.h \
        Navig/BarcodePrinter/Printer.h \
        Navig/Navig.h \
        MenuInfoPages/InfoView.h \
        MenuInfoPages/Partners.h \
        MenuInfoPages/Description.h \
        MenuInfoPages/Timetable.h \
        MenuInfoPages/Instruct.h \
    RegistrationForm.h

FORMS += \
        Menu.ui \
        ReturnButton.ui \
        Navig/Navig.ui \
        MenuInfoPages/InfoView.ui \
        MenuInfoPages/Partners.ui \
        MenuInfoPages/Description.ui \
        MenuInfoPages/Timetable.ui \
        MenuInfoPages/Instruct.ui \
    RegistrationForm.ui


