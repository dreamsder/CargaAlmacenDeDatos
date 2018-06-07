#-------------------------------------------------
#
# Project created by QtCreator 2012-12-26T12:07:58
#
#-------------------------------------------------

QT       += core gui console sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CargaAlmacenDeDatos
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Utilidades/database.cpp \
    procesarinformacion.cpp \
    Utilidades/configuracionxml.cpp \
    Utilidades/logs.cpp

HEADERS  += mainwindow.h \
    Utilidades/database.h \
    procesarinformacion.h \
    Utilidades/configuracionxml.h \
    Utilidades/logs.h

FORMS    += mainwindow.ui
