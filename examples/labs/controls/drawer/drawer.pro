TEMPLATE = app
TARGET = drawer
QT += quick

SOURCES += \
    main.cpp

OTHER_FILES += \
    main.qml

RESOURCES += \
    drawer.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/labs/controls/drawer
INSTALLS += target