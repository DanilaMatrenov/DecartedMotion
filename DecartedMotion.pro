QT       += core gui \
    quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += sql
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



SOURCES += \
    dbconnection.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp

HEADERS += \
    dbconnection.h \
    mainwindow.h \
    model.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -LF:/psql/lib/ -llibpq
else:win32:CONFIG(debug, debug|release): LIBS += -LF:/psql/lib/ -llibpqd
else:unix: LIBS += -LF:/psql/lib/ -llibpq

INCLUDEPATH += F:/psql/include
DEPENDPATH += F:/psql/include
