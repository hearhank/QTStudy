QT += quick core network

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        codebehind.cpp \
        main.cpp \
        udpsenderreceiver.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    codebehind.hpp \
    udpsenderreceiver.hpp

#LIBS +="-L$$OUT_PWD/../LibNet/debug/LibNet.dll"

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LibNet/release/ -lLibNet
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LibNet/debug/ -lLibNet

#INCLUDEPATH += $$PWD/../LibNet
#DEPENDPATH += $$PWD/../LibNet

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LibNet/release/libLibNet.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LibNet/debug/libLibNet.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LibNet/release/LibNet.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LibNet/debug/LibNet.lib

#win32: LIBS += -lLibNet

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-QTStudy-Desktop_Qt_5_12_6_MinGW_64_bit-Debug/LibNet/release/ -lLibNet
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-QTStudy-Desktop_Qt_5_12_6_MinGW_64_bit-Debug/LibNet/debug/ -lLibNet

INCLUDEPATH += $$PWD/../LibNet
DEPENDPATH += $$PWD/../LibNet

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build-QTStudy-Desktop_Qt_5_12_6_MinGW_64_bit-Debug/LibNet/release/libLibNet.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build-QTStudy-Desktop_Qt_5_12_6_MinGW_64_bit-Debug/LibNet/debug/libLibNet.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build-QTStudy-Desktop_Qt_5_12_6_MinGW_64_bit-Debug/LibNet/release/LibNet.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build-QTStudy-Desktop_Qt_5_12_6_MinGW_64_bit-Debug/LibNet/debug/LibNet.lib
