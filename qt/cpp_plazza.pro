#-------------------------------------------------
#
# Project created by QtCreator 2016-04-11T18:51:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = plazza_gui


SOURCES +=  main.cpp\
            ../sources/Window.cpp \
            ../sources/ThreadPool.cpp \
            ../sources/ProcessManager.cpp \
            ../sources/Process.cpp \
            ../sources/NamedPipe.cpp \
            ../sources/Xor.cpp \
            ../sources/AEncryptionMethod.cpp \
            ../sources/Cesar.cpp \
            ../sources/ProcessData.cpp \
            ../sources/Parser.cpp \
            ../sources/Log.cpp \
            ../sources/BruteForcer.cpp

HEADERS  += ../includes/Window.hpp

INCLUDEPATH +=  += ../includes/


FORMS    += forms/mainwindow.ui

LIBS += \
  -lboost_regex \

DISTFILES += \
    ressources/pizzera.jpg \
    ressources/pizzeria.png \
    ressources/icon.png

QMAKE_CXXFLAGS += -std=c++11
