INCLUDEPATH += . ..

########About Widget########
HEADERS += \
    $$PWD/Options/CompilerOptionsWidget.h \
    $$PWD/Options/EditorOptionsWidget.h \
    $$PWD/Output/CompilerOutputWidget.h \
    $$PWD/Output/ApplicationOutputWidget.h \
    $$PWD/Output/ErrorOutputWidget.h \
    $$PWD/Output/ClipBoardWidget.h \
    $$PWD/Output/OutputWidget.h \
    $$PWD/Output/OutputBaseWidget.h \
    $$PWD/Output/OutputMenubarWidget.h
SOURCES += \
    $$PWD/Options/CompilerOptionsWidget.cpp \
    $$PWD/Options/EditorOptionsWidget.cpp \
    $$PWD/Output/CompilerOutputWidget.cpp \
    $$PWD/Output/ApplicationOutputWidget.cpp \
    $$PWD/Output/ErrorOutputWidget.cpp \
    $$PWD/Output/ClipBoardWidget.cpp \
    $$PWD/Output/OutputWidget.cpp \
    $$PWD/Output/OutputMenubarWidget.cpp
FORMS += \
    $$PWD/Options/CompilerOptionsWidget.ui \
    $$PWD/Options/EditorOptionsWidget.ui \
    $$PWD/Output/OutputMenubarWidget.ui

########Code Editor Widget########
HEADERS += \
    $$PWD/CodeEditor/EditorStatusWidget.h
SOURCES += \
    $$PWD/CodeEditor/EditorStatusWidget.cpp
FORMS += \
    $$PWD/CodeEditor/EditorStatusWidget.ui

########File Browser Widget########
HEADERS += \
    $$PWD/FileBrowser/FileBrowserWidget.h \
    $$PWD/FileBrowser/FileBrowserController.h
SOURCES += \
    $$PWD/FileBrowser/FileBrowserWidget.cpp \
    $$PWD/FileBrowser/FileBrowserController.cpp

########Library Widget########
HEADERS += \
    $$PWD/Library/ProgramLibraryController.h \
    $$PWD/Library/ProgramLibraryDialog.h \
    $$PWD/Library/ProgramLibraryWidget.h \
    $$PWD/Library/ProgramLibraryToolbar.h \
    $$PWD/Library/AddToLibraryWidget.h \
    $$PWD/Library/AddToLibraryController.h
SOURCES += \
    $$PWD/Library/ProgramLibraryController.cpp \
    $$PWD/Library/ProgramLibraryDialog.cpp \
    $$PWD/Library/ProgramLibraryWidget.cpp \
    $$PWD/Library/ProgramLibraryToolbar.cpp \
    $$PWD/Library/AddToLibraryWidget.cpp \
    $$PWD/Library/AddToLibraryController.cpp
FORMS += \
    $$PWD/Library/ProgramLibraryToolbar.ui \
    $$PWD/Library/AddToLibraryWidget.ui

########Options Widget########
HEADERS += \
    $$PWD/Options/OptionsController.h \
    $$PWD/Options/OptionsDialog.h \
    $$PWD/Options/OptionsWidget.h
SOURCES += \
    $$PWD/Options/OptionsController.cpp \
    $$PWD/Options/OptionsDialog.cpp \
    $$PWD/Options/OptionsWidget.cpp

########Workspace Widget########
HEADERS += \
    $$PWD/Workspace/WorkspaceDialog.h
SOURCES += \
    $$PWD/Workspace/WorkspaceDialog.cpp
FORMS += \
    $$PWD/Workspace/WorkspaceDialog.ui

########About Widget########
HEADERS += \
    $$PWD/About/AboutDialog.h
SOURCES += \
    $$PWD/About/AboutDialog.cpp
FORMS += \
    $$PWD/About/AboutDialog.ui
