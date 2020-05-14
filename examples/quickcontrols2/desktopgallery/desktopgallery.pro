QT += quick quickcontrols2

SOURCES += \
        main.cpp

QML_FILES = \
    main.qml \
    ControlContainer.qml \
    Buttons.qml \
    CustomButtons.qml \
    Sliders.qml \
    CustomSliders.qml \
    CheckBoxes.qml \
    CustomCheckBoxes.qml \
    RadioButtons.qml \
    CustomRadioButtons.qml \
    SpinBoxes.qml \
    CustomSpinBoxes.qml \

OTHER_FILES += $$QML_FILES
RESOURCES += $$QML_FILES
RESOURCES += checkbox-icon.png checkbox-icon16.png checkbox-icon@2x.png

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols2/desktopgallery
INSTALLS += target
