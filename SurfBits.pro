#-------------------------------------------------
#
# Project created by QtCreator 2016-03-28T15:44:41
#
#-------------------------------------------------

QT       += core gui network webkit webkitwidgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SurfBits
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
        Link.cpp \
        AddressModel.cpp \
        PendingModel.cpp \
        ReadyModel.cpp \
        AddLinkDialog.cpp \
        FileManager.cpp

HEADERS  += MainWindow.h \
        Link.h \
        AddressModel.h \
        PendingModel.h \
        ReadyModel.h \
        AddLinkDialog.h \
        FileManager.h

FORMS    += MainWindow.ui \
        AddLinkDialog.ui

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
        Res.qrc

RC_ICONS += SurfBits.ico
#RC_FILE += SurfBits_resource.rc
