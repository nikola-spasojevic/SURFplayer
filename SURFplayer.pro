#-------------------------------------------------
#
# Project created by QtCreator 2015-02-14T18:33:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SURFplayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    mouse_tracker.cpp \
    addobjectdialog.cpp

HEADERS  += mainwindow.h \
    player.h \
    mouse_tracker.h \
    addobjectdialog.h

FORMS    += mainwindow.ui \
    addobjectdialog.ui

LIBS += -L/usr/local/Cellar/opencv/2.4.9/lib \
-lopencv_core \
-lopencv_highgui \
-lopencv_imgproc \
-lopencv_flann \
-lopencv_legacy \
-lopencv_ml \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_nonfree

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/opencv/2.4.9/include
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/opencv/2.4.9/include

DISTFILES +=
