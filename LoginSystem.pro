QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_LFLAGS += -no-pie

SOURCES += \
    coordinator.cpp \
    logincoordinator.cpp \
    loginstudent.cpp \
    main.cpp \
    mainwindow.cpp \
    student.cpp \
    instructor.cpp \
    instructorlogin.cpp

HEADERS += \
    coordinator.h \
    logincoordinator.h \
    loginstudent.h \
    mainwindow.h \
    student.h \
    instructor.h \
    instructorlogin.h

FORMS += \
    coordinator.ui \
    logincoordinator.ui \
    loginstudent.ui \
    mainwindow.ui \
    student.ui \
    instructor.ui \
    instructorlogin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
