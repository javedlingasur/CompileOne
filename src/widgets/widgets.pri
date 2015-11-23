INCLUDEPATH += . ..

########About Widget########
HEADERS += \
    $$PWD/Output/OutputWidget.h
SOURCES += \
    $$PWD/Output/OutputWidget.cpp
FORMS += \
    $$PWD/Output/OutputWidget.ui

########Code Editor Widget########
HEADERS += \
    $$PWD/CodeEditor/CodeEditor.h \
    $$PWD/CodeEditor/Highlighter.h \
    $$PWD/CodeEditor/EditorController.h \
    $$PWD/CodeEditor/EditorStatusWidget.h
SOURCES += \
    $$PWD/CodeEditor/CodeEditor.cpp \
    $$PWD/CodeEditor/Highlighter.cpp \
    $$PWD/CodeEditor/EditorController.cpp \
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
    $$PWD/Options/OptionsWidget.h \
    $$PWD/Options/ChangeWorkSpaceWidget.h
SOURCES += \
    $$PWD/Options/OptionsController.cpp \
    $$PWD/Options/OptionsDialog.cpp \
    $$PWD/Options/OptionsWidget.cpp \
    $$PWD/Options/ChangeWorkSpaceWidget.cpp
FORMS += \
    $$PWD/Options/OptionsWidget.ui \
    $$PWD/Options/ChangeWorkSpaceWidget.ui

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
