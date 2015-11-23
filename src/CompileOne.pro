QT += widgets

CONFIG += c++11 release qscintilla2

macx {
    QMAKE_POST_LINK = install_name_tool -change libqscintilla2.12.dylib $$[QT_INSTALL_LIBS]/libqscintilla2.12.dylib $(TARGET)
}


release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

include( app/app.pri )
include( core/core.pri )
include( common/common.pri )
include( utility/utility.pri )
include( widgets/widgets.pri )

RESOURCES     = ../resources/application.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
INSTALLS += target


