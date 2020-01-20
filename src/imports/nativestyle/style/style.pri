INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/qquickcommonstyle.h \
    $$PWD/qquickcommonstyle_p.h \
    $$PWD/qquickcommonstylepixmaps_p.h \
    $$PWD/qquickdrawutil.h \
    $$PWD/qquickstyle.h \
    $$PWD/qquickstyle_p.h \
    $$PWD/qquickstylehelper_p.h \
    $$PWD/qquickstyleoption.h

SOURCES += \
    $$PWD/qquickcommonstyle.cpp \
    $$PWD/qquickdrawutil.cpp \
    $$PWD/qquickstyle.cpp \
    $$PWD/qquickstylehelper.cpp \
    $$PWD/qquickstyleoption.cpp

osx: include(mac/mac.pri)
