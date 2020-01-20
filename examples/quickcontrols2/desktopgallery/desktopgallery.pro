QT += quick quickcontrols2

SOURCES += \
        main.cpp

RESOURCES += qml.qrc
RESOURCES += checkbox-icon.png checkbox-icon16.png checkbox-icon@2x.png

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols2/desktopgallery
INSTALLS += target
