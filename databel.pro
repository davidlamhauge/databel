QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

VERSION = 0.9
DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    diviopgaver.cpp \
    gangeopgaver.cpp \
    main.cpp \
    mainwindow.cpp \
    minusopgaver.cpp \
    plusopgaver.cpp \
    solvetasks.cpp

HEADERS += \
    diviopgaver.h \
    gangeopgaver.h \
    mainwindow.h \
    minusopgaver.h \
    plusopgaver.h \
    solvetasks.h

FORMS += \
    diviopgaver.ui \
    gangeopgaver.ui \
    mainwindow.ui \
    minusopgaver.ui \
    plusopgaver.ui \
    solvetasks.ui

TRANSLATIONS += \
    lang/daspelling_en.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
