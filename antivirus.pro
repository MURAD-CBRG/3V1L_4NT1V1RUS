QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addfiletodbdialog.cpp \
    analizerseparated.cpp \
    configuredialog.cpp \
    database_api.cpp \
    dir_reader.cpp \
    main.cpp \
    antiviruswindow.cpp \
    signature.cpp \
    sqllite/shell.c \
    sqllite/sqlite3.c \
    sha256/sha256.cpp \
    bypass.cpp \
    conf.cpp

HEADERS += \
    addfiletodbdialog.h \
    analizerseparated.h \
    antiviruswindow.h \
    bypass.h \
    configuredialog.h \
    database_api.h \
    dir_reader.h \
    signature.h \
    sqllite/sqlite3ext.h \
    sqllite/sqlite3.h \
    sha256/sha256.h \
    conf.h


FORMS += \
    addfiletodbdialog.ui \
    antiviruswindow.ui \
    configuredialog.ui

RC_ICONS = sprites/anti.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    sprites/anti.png \
    virus_test_database.db

RESOURCES += \
    tray_icon.qrc
