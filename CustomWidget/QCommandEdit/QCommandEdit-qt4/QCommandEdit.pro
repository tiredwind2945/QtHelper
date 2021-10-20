# QCommandEdit - a command input widget with history and tab completion
# Copyright (C) 2018 Federico Ferri

QT       += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

TARGET = QCommandEdit
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcommandedit.cpp \
    qcommandtokenizer.cpp

HEADERS += \
    mainwindow.h \
    qcommandedit.h \
    qcommandtokenizer.h

FORMS += \
    mainwindow.ui

DEFINES += \
    QT_DISABLE_DEPRECATED_BEFORE=0x060000 \
    QT_RESTRICTED_CAST_FROM_ASCII \
    QT_NO_KEYWORDS
