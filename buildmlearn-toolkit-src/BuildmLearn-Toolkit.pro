QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TFT
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    newprojectwidget.cpp \
    GlobalData.cpp \
    InfoTemplate.cpp \
    QuizTemplate.cpp \
    QuestionItem.cpp \
    FlashcardTemplate.cpp

HEADERS  +=  mainwindow.h \
    newprojectwidget.h \
    GlobalData.h \
    InfoTemplate.h \
    QuizTemplate.h \
    QuestionItem.h \
    FlashcardTemplate.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    LICENSE.txt

RESOURCES += \
    images.qrc
