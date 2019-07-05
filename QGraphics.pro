#-------------------------------------------------
#
# Project created by QtCreator 2019-07-03T09:17:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGraphics
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
        cmainwindow.cpp \
    cgraphics/cgraphics.cc \
    cgraphics/cgrcolor.cc \
    cgraphics/cgrdata.cc \
    cgraphics/cgrlinestyle.cc \
    cgraphics/cgrmousepoint.cc \
    cgraphics/cgrpoint.cc \
    cgraphics/cgrrect.cc \
    cgraphics/ivideo.cc \
    clabel_imagearea.cpp \
    interpolation/ccubicspline.cc \
    interpolation/iinterpolater.cc \
    interpolation/clinear.cc \
    interpolation/cquadric.cc \
    cgraphics/igraphics.cc \
    interpolation/cquadricspline.cc \
    cgraphics/cvideo_software.cc \
    interpolation/cstep.cc \
    cgraphics/cvideo_qt.cc

HEADERS += \
        cmainwindow.h \
    cgraphics/cgraphics.h \
    cgraphics/cgrcolor.h \
    cgraphics/cgrdata.h \
    cgraphics/cgrlinestyle.h \
    cgraphics/cgrmousepoint.h \
    cgraphics/cgrpoint.h \
    cgraphics/cgrrect.h \
    cgraphics/ivideo.h \
    clabel_imagearea.h \
    interpolation/ccubicspline.h \
    interpolation/iinterpolater.h \
    interpolation/clinear.h \
    interpolation/cquadric.h \
    cgraphics/igraphics.h \
    interpolation/cquadricspline.h \
    interpolation/cstep.h \
    cgraphics/cvideo_qt.h \
    cgraphics/cvideo_software.h
FORMS += \
        cmainwindow.ui
