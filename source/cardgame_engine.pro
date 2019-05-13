#-------------------------------------------------
#
# Project created by QtCreator 2019-03-06T14:05:41
#
#-------------------------------------------------

QT       += core gui network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cardgame_engine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    OpenGLEngine/oglemastercontroller.cpp \
    OpenGLEngine/oglewindow.cpp \
    ExampleGames/tennis/tennis.cpp \
    ExampleGames/tennis/tennis_script.cpp \
    OpenGLEngine/ogleemblem.cpp \
    ExampleGames/tennis/playerTools/paddle.cpp \
    OpenGLEngine/oglewindowmouseposition.cpp \
    OpenGLEngine/ogleemblem/ogleemblembox.cpp

HEADERS += \
    OpenGLEngine/oglemastercontroller.h \
    OpenGLEngine/oglewindow.h \
    ExampleGames/tennis/tennis.h \
    ExampleGames/tennis/tennis_script.h \
    OpenGLEngine/ogleemblem.h \
    ExampleGames/tennis/playerTools/paddle.h \
    OpenGLEngine/oglewindowmouseposition.h \
    OpenGLEngine/ogleemblem/ogleemblembox.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
