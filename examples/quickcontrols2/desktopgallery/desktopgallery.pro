QT += quick quickcontrols2

SOURCES += \
        main.cpp

QML_FILES = \
    main.qml \
    Buttons.qml \
    Sliders.qml \
    CheckBoxes.qml \
    ControlContainer.qml \

OTHER_FILES += $$QML_FILES
RESOURCES += $$QML_FILES
RESOURCES += checkbox-icon.png checkbox-icon16.png checkbox-icon@2x.png

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols2/desktopgallery
INSTALLS += target
