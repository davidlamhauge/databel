QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

VERSION = 0.9
DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    preferencemanager.cpp \
    solvetasks.cpp

HEADERS += \
    mainwindow.h \
    preferencemanager.h \
    solvetasks.h

FORMS += \
    mainwindow.ui \
    preferencemanager.ui \
    solvetasks.ui

TRANSLATIONS += \
    lang/databel_da.ts \
    lang/databel_en.ts \
    lang/databel_fo.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES += \
    lang/databel_da.qm \
    lang/databel_en.qm
