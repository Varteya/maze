#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T00:24:06
#
#-------------------------------------------------

QT       += widgets opengl

CONFIG += c++11

TARGET = Maze
TEMPLATE = app


SOURCES += main.cpp\
    glwidget.cpp \
    field.cpp \
    player.cpp

HEADERS  += \
    field.h \
    glwidget.h \
    Player.h

FORMS    +=

OTHER_FILES += \
    text_map.txt \
    1.fsh \
    1.vsh

RESOURCES += \
    textures.qrc

DESTDIR = $$PWD
