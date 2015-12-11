/***************************************************************************
*Copyright (c) 2015 Javed Lingasur
*
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all
*copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*SOFTWARE.
***************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widgets/CodeEditor/CodeEditor.h"
#include "common/QtIncludes.h"
#include "widgets/FileBrowser/FileBrowserWidget.h"
#include "widgets/Options/OptionsDialog.h"
#include "widgets/About/AboutDialog.h"
#include "widgets/Library/ProgramLibraryDialog.h"
#include "widgets/Library/AddToLibraryWidget.h"
#include "widgets/CodeEditor/EditorStatusWidget.h"
#include "widgets/Output/OutputWidget.h"

using namespace Co::Output;

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = 0 );

    void setWorkspacePath( QString strPath );

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void openLibrary();
    void addToLibrary();
    void about();
    void documentWasModified();
    void compileCode();
    void runCode();
    void options();

    void showFileInEditor( QString qstrFileName );

public:
    void initializeEditor();
    void initializeLexer();
    void initializeFolding();
    void initializeMargin();
    void initializeCaretLine();
    void initializeFont();
    QStringList parseErrorMessage( const QString &compilerOutpur );

public slots:
    void onTextChanged();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QPlainTextEdit *m_compileOutputText;
    QString curFile;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *buildMenu;
    QMenu *toolsMenu;
    QMenu *LibraryMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *buildToolBar;
    QToolBar *LibraryToolBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *openLibraryAct;
    QAction *addToLibAct;
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *compileAct;
    QAction *runAct;
    QAction *optionsAct;

//    CodeEditor* m_codeeditor;
    QsciScintilla *m_codeeditor;
    QProcess* m_CMDProcess;

    QPlainTextEdit *m_ReplaceWithTree;
    FileBrowserWidget *m_fileBrowserWidget;
    OptionsDialog *m_OptionsDialog;
    AboutDialog *m_AboutDialog;
    ProgramLibraryDialog *m_ProgramLibraryDialog;
    AddToLibraryWidget *m_AddToLibraryWidget;

//    OutputBaseWidget* m_OutputWidget;
    EditorStatusWidget* m_EditorStatusWidget;

    OutputBaseWidget::ptr m_errorOutputWidget;
    OutputBaseWidget::ptr m_compilerOutputWidget;
    OutputBaseWidget::ptr m_applicationOutputWidget;
    OutputBaseWidget::ptr m_clipBoardWidget;
};

#endif
