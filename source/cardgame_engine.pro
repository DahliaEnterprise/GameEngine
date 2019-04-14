#-------------------------------------------------
#
# Project created by QtCreator 2019-03-06T14:05:41
#
#-------------------------------------------------

QT       += core gui

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
    gameengine.cpp \
    gameengine/opengl.cpp \
    gameengine/opengl_canvas.cpp \
    examplegame/gameloop.cpp \
    head.cpp \
    gameengine/gameobject.cpp \
    examplegame/keyboardMouseInput/keyboardmouseinput.cpp \
    examplegame/quickgame/quickgame.cpp \
    examplegame/quickgame/card/card_creature.cpp \
    examplegame/quickgame/card/card_moduspraecptum.cpp \
    examplegame/quickgame/module/card/module_card_hightlightable.cpp \
    examplegame/quickgame/card/card_turnactivatedcard.cpp \
    examplegame/quickgame/module/card/module_card_clickable.cpp \
    #examplegame/keyboardMouseInput/keyboardmouseinput.cpp \
    examplegame/mainmenu/character/charazard.cpp \
    examplegame/mainmenu/mainmenu.cpp \
    examplegame/quickgame/card/card_creature.cpp \
    examplegame/quickgame/card/card_moduspraecptum.cpp \
    examplegame/quickgame/card/card_turnactivatedcard.cpp \
    examplegame/quickgame/module/card/module_card_clickable.cpp \
    examplegame/quickgame/module/card/module_card_hightlightable.cpp \
    examplegame/quickgame/quickgame.cpp \
    examplegame/gameloop.cpp \
    gameengine/gameobject.cpp \
    gameengine/opengl.cpp \
    gameengine/opengl_canvas.cpp \
    gameengine.cpp \
    head.cpp \
    main.cpp

HEADERS += \
    gameengine.h \
    gameengine/opengl.h \
    gameengine/opengl_canvas.h \
    examplegame/gameloop.h \
    head.h \
    gameengine/gameobject.h \
    examplegame/keyboardMouseInput/keyboardmouseinput.h \
    examplegame/quickgame/quickgame.h \
    examplegame/quickgame/card/card_creature.h \
    examplegame/quickgame/card/card_moduspraecptum.h \
    examplegame/quickgame/module/card/module_card_hightlightable.h \
    examplegame/quickgame/card/card_turnactivatedcard.h \
    examplegame/quickgame/module/card/module_card_clickable.h \
    #examplegame/keyboardMouseInput/keyboardmouseinput.h \
    examplegame/mainmenu/character/charazard.h \
    examplegame/mainmenu/mainmenu.h \
    examplegame/quickgame/card/card_creature.h \
    examplegame/quickgame/card/card_moduspraecptum.h \
    examplegame/quickgame/card/card_turnactivatedcard.h \
    examplegame/quickgame/module/card/module_card_clickable.h \
    examplegame/quickgame/module/card/module_card_hightlightable.h \
    examplegame/quickgame/quickgame.h \
    examplegame/gameloop.h \
    gameengine/gameobject.h \
    gameengine/opengl.h \
    gameengine/opengl_canvas.h \
    gameengine.h \
    head.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
