QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    transformlistview.cpp \
    transformtask.cpp

HEADERS += \
    mainwindow.h \
    transformlistview.h \
    transformtask.h

FORMS += \
    mainwindow.ui

mySetOfExtraFiles.files = $$PWD/etc1tool
mySetOfExtraFiles.path = Contents/MacOS
QMAKE_BUNDLE_DATA += mySetOfExtraFiles
message($$OUT_PWD)

CONFIG += debug_and_release

CONFIG(release, debug|release) {
message(release build!)
 QMAKE_POST_LINK += macdeployqt $$OUT_PWD/$${TARGET}.app
}

CONFIG(debug, debug|release) {
message(debug build!)
}

ICON = icon.icns
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
