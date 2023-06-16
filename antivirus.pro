QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    antiviruswindow.cpp \
    antivirus.cpp \
#    test.cpp \
    sqllite/shell.c \
    sqllite/sqlite3.c \
    sha256/sha256.cpp

HEADERS += \
    antiviruswindow.h \
    antivirus.h \
#    test.h \
    sqllite/sqlite3ext.h \
    sqllite/sqlite3.h \
    sha256/sha256.h


FORMS += \
    antiviruswindow.ui

RC_ICONS = sprites/anti.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    sprites/anti.png
