/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <functional>
#include <memory>

#include "mainwindow.h"

#include "utility/SettingsManager.h"

#include "widgets/Workspace/WorkspaceDialog.h"
#include "widgets/Output/ErrorOutputWidget.h"
#include "widgets/Output/CompilerOutputWidget.h"
#include "widgets/Output/ApplicationOutputWidget.h"
#include "widgets/Output/ClipBoardWidget.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow( parent ),
    m_OptionsDialog( 0 ),
    m_AboutDialog( 0 ),
    m_ProgramLibraryDialog( 0 ),
    m_AddToLibraryWidget( 0 ),
    m_EditorStatusWidget( 0 )
//  ,    m_OutputWidget( 0 )
{
//    setWindowFlags( Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint );
    this->setContentsMargins( 0, 0, 0, 0 );
    QWidget* baseEditorWidget = new QWidget(this);

    QSplitter *vSplitter = new QSplitter;
    vSplitter->setFixedWidth(0);
    vSplitter->setOrientation(Qt::Vertical);
    vSplitter->setLineWidth(0);
    vSplitter->setHandleWidth(0);

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setContentsMargins(0,0,0,0);

//    m_codeeditor = new CodeEditor();



    m_codeeditor = new QsciScintilla(this);
    m_codeeditor->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn);
    m_codeeditor->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn);
    m_codeeditor->setAutoCompletionCaseSensitivity(true);
//    m_codeeditor->setFrameShape(QFrame::NoFrame);

    m_EditorStatusWidget = new EditorStatusWidget(this);

//    highlighter = new Highlighter(m_codeeditor->document());
    m_compileOutputText = new QPlainTextEdit();
    m_compileOutputText->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
                                                     "color: rgb(255, 255, 0);"));

//    m_OutputWidget = new OutputBaseWidget( this );

    vSplitter->addWidget(m_codeeditor);
//    vSplitter->addWidget(m_OutputWidget);
    using namespace Co::Output;
    QWidget* outBaseWidget = new QWidget(this);
    QVBoxLayout *vBoxLayout1 = new QVBoxLayout;
    vBoxLayout1->setContentsMargins(0,0,0,0);
    OutputWidgetHolder::setParent(outBaseWidget);
    vBoxLayout1->addWidget(OutputWidgetHolder::getInstance());

    using namespace Co::Output;
    m_errorOutputWidget = std::make_shared< ErrorOutputWidget > ();
    m_compilerOutputWidget = std::make_shared< CompilerOutputWidget > ();
    m_applicationOutputWidget = std::make_shared< ApplicationOutputWidget > ();
    m_clipBoardWidget = std::make_shared< ClipBoardWidget > ();

    OutputWidgetHolder::getInstance()->addOutputPage(m_errorOutputWidget->getName(),m_errorOutputWidget.get());
    OutputWidgetHolder::getInstance()->addOutputPage(m_compilerOutputWidget->getName(),m_compilerOutputWidget.get());
    OutputWidgetHolder::getInstance()->addOutputPage(m_applicationOutputWidget->getName(),m_applicationOutputWidget.get());
    OutputWidgetHolder::getInstance()->addOutputPage(m_clipBoardWidget->getName(),m_clipBoardWidget.get());
outBaseWidget->setLayout(vBoxLayout1);
        vSplitter->addWidget(outBaseWidget);

    QList<int> vList= vSplitter->sizes();
    vList.replace(0,this->height()/0.3);
    vList.replace(1,this->height()/0.7);
    vSplitter->setSizes(vList);

    vBoxLayout->addWidget(vSplitter);
    baseEditorWidget->setLayout(vBoxLayout);

    QWidget* baseWidget = new QWidget(this);

    QSplitter *hSplitter = new QSplitter;
    hSplitter->setFixedWidth(0);
    hSplitter->setOrientation(Qt::Horizontal);
    hSplitter->setFrameShape(QFrame::NoFrame);
    hSplitter->setLineWidth(0);
    hSplitter->setHandleWidth(0);

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->setContentsMargins(0,0,0,0);

    m_ReplaceWithTree = new QPlainTextEdit();
    m_fileBrowserWidget = new FileBrowserWidget(this);

    hSplitter->addWidget(m_fileBrowserWidget);
    hSplitter->addWidget(baseEditorWidget);

    QList<int> hList= hSplitter->sizes();
    hList.replace(0,this->height()/0.8);
    hList.replace(1,this->height()/0.2);
    hSplitter->setSizes(hList);

    hBoxLayout->addWidget(hSplitter);
    baseWidget->setLayout(hBoxLayout);

    this->setCentralWidget(baseWidget);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    initializeEditor();

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);    

    //SIGNALS WILL BE COUGHT FROM DIFFERENT WIDGETS
    connect(m_fileBrowserWidget,SIGNAL(showFileInEditor(QString)),this,SLOT(showFileInEditor( QString )));

    connect(m_codeeditor,SIGNAL(cursorPositionChanged(int,int)),m_EditorStatusWidget,SLOT(update(int,int)));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        m_codeeditor->clear();
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString qstrWorkPath = SettingsManager::Instance()->readSettings( Settings::WORKSPACE_PATH ).toString();
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDirectory( QDir(qstrWorkPath));
    dialog.exec();
    QStringList files = dialog.selectedFiles();

    if (files.isEmpty())
        return false;

    return saveFile(files.at(0));
}

void MainWindow::about()
{
    if( ! m_AboutDialog) {
        m_AboutDialog = new AboutDialog( this );
    }
    if( m_AboutDialog->exec() == QDialog::Accepted )
    {
    }
}

void MainWindow::documentWasModified()
{
//    setWindowModified(m_codeeditor->document()->isModified());
    setWindowModified(m_codeeditor->isModified());
}

void MainWindow::createActions()

{
    newAct = new QAction(QIcon(":/icons/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/icons/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/icons/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    openLibraryAct = new QAction(QIcon(":/icons/programLibrary.png"), tr("Open Library..."), this);
    openLibraryAct->setShortcut(QKeySequence(Qt::Key_L + Qt::CTRL));
    openLibraryAct->setStatusTip(tr("Open program library"));
    connect(openLibraryAct, SIGNAL(triggered()), this, SLOT(openLibrary()));

    addToLibAct = new QAction(QIcon(":/icons/addToLibrary.png"), tr("Add To Library"), this );
    addToLibAct->setStatusTip(tr("Add program to library"));
    connect(addToLibAct, SIGNAL(triggered()), this, SLOT(addToLibrary()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    cutAct = new QAction(QIcon(":/icons/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), m_codeeditor, SLOT(cut()));

    copyAct = new QAction(QIcon(":/icons/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), m_codeeditor, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/icons/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), m_codeeditor, SLOT(paste()));

    undoAct = new QAction(QIcon(":/icons/undo.png"), tr("&Undo"), this);
    undoAct->setShortcut(QKeySequence(Qt::Key_Z + Qt::CTRL));
    undoAct->setStatusTip(tr("Undo"));
    connect(undoAct, SIGNAL(triggered()), m_codeeditor, SLOT(undo()));

    redoAct = new QAction(QIcon(":/icons/redo.png"), tr("&Redo"), this);
    redoAct->setShortcut(QKeySequence(Qt::Key_Y + Qt::CTRL));
    redoAct->setStatusTip(tr("Redo"));
    connect(redoAct, SIGNAL(triggered()), m_codeeditor, SLOT(redo()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(m_codeeditor, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(m_codeeditor, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));

    compileAct = new QAction(QIcon(":/icons/compile.png"),tr("Compile"),this);
    compileAct->setShortcut(QKeySequence(Qt::Key_F9));
    compileAct->setStatusTip(tr("Compile the file"));
    connect(compileAct, SIGNAL(triggered()), this, SLOT(compileCode()));

    runAct = new QAction(QIcon(":/icons/run.png"),tr("Run"),this);
    runAct->setShortcut(QKeySequence(Qt::Key_R + Qt::CTRL));
    runAct->setStatusTip(tr("Run the compiled file"));
    connect(runAct, SIGNAL(triggered()), this, SLOT(runCode()));

    optionsAct = new QAction(QIcon(":/icons/options.png"),tr("Options..."),this);
    optionsAct->setShortcut(QKeySequence(Qt::Key_O + Qt::CTRL));
    optionsAct->setStatusTip(tr("Show the options window"));
    connect(optionsAct, SIGNAL(triggered()), this, SLOT(options()));

    showFileToolbarAct  = new QAction(tr("File"),this);
    showFileToolbarAct->setCheckable(true);
    connect(showFileToolbarAct,SIGNAL(toggled(bool)),this,SLOT(showFileToolbar(bool)));

    showEditToolbarAct  = new QAction(tr("Edit"),this);
    showEditToolbarAct->setCheckable(true);
    connect(showEditToolbarAct,SIGNAL(toggled(bool)),this,SLOT(showEditToolbar(bool)));

    showBuildToolbarAct = new QAction(tr("Build"),this);
    showBuildToolbarAct->setCheckable(true);
    connect(showBuildToolbarAct,SIGNAL(toggled(bool)),this,SLOT(showBuildToolbar(bool)));

    showLibToolbarAct   = new QAction(tr("Library"),this);
    showLibToolbarAct->setCheckable(true);
    connect(showLibToolbarAct,SIGNAL(toggled(bool)),this,SLOT(showLibToolbar(bool)));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    viewMenu = menuBar()->addMenu(tr("&View"));
    shoeToolBar = viewMenu->addMenu(tr("Toolbar"));
    shoeToolBar->addAction(showFileToolbarAct );
    shoeToolBar->addAction(showEditToolbarAct );
    shoeToolBar->addAction(showBuildToolbarAct);
    shoeToolBar->addAction(showLibToolbarAct  );

    buildMenu = menuBar()->addMenu(tr("&Build"));
    buildMenu->addAction(compileAct);
    buildMenu->addAction(runAct);

    LibraryMenu = menuBar()->addMenu(tr("&Library"));
    LibraryMenu->addAction(openLibraryAct);
    LibraryMenu->addAction(addToLibAct);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(optionsAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->setAllowedAreas(Qt::LeftToolBarArea);
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->setStyleSheet(QLatin1String("height: 14px;\n"
                                             "width: 14px;"));
    this->addToolBar(Qt::LeftToolBarArea,fileToolBar);
    connect(fileToolBar,SIGNAL(visibilityChanged(bool)),this,SLOT(setShowFileToolbarAct(bool)));

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->setAllowedAreas(Qt::LeftToolBarArea);
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
    editToolBar->setStyleSheet(QLatin1String("height: 14px;\n"
                                             "width: 14px;"));
    this->addToolBar(Qt::LeftToolBarArea,editToolBar);
    connect(editToolBar,SIGNAL(visibilityChanged(bool)),this,SLOT(setShowEditToolbarAct(bool)));

    buildToolBar = addToolBar(tr("Build"));
    buildToolBar->setAllowedAreas(Qt::LeftToolBarArea);
    buildToolBar->addAction(compileAct);
    buildToolBar->addAction(runAct);
    buildToolBar->setStyleSheet(QLatin1String("height: 14px;\n"
                                              "width: 14px;"));
    this->addToolBar(Qt::LeftToolBarArea,buildToolBar);
    connect(buildToolBar,SIGNAL(visibilityChanged(bool)),this,SLOT(setShowBuildToolbarAct(bool)));

    LibraryToolBar = addToolBar(tr("Library"));
    LibraryToolBar->setAllowedAreas(Qt::LeftToolBarArea);
    LibraryToolBar->addAction(openLibraryAct);
    LibraryToolBar->addAction(addToLibAct);
    LibraryToolBar->setStyleSheet(QLatin1String("height: 14px;\n"
                                              "width: 14px;"));
    this->addToolBar(Qt::LeftToolBarArea,LibraryToolBar);
    connect(LibraryToolBar,SIGNAL(visibilityChanged(bool)),this,SLOT(setShowLibToolbarAct(bool)));
}

void MainWindow::createStatusBar()
{
    statusBar()->addPermanentWidget(m_EditorStatusWidget,0);
    statusBar()->showMessage(tr("Ready"));
//    statusBar()->
}

void MainWindow::readSettings()
{
    QSettings settings("QtProject", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings("QtProject", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

bool MainWindow::maybeSave()
{
    if (m_codeeditor->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    m_codeeditor->setText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << m_codeeditor->text();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    m_codeeditor->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::compileCode()
{
    QString program = SettingsManager::Instance()->readSettings(Settings::COMPILER_PATH).toString();
    QStringList arguments;
    arguments << curFile;

    QProcess *myProcess = new QProcess(this);
    myProcess->start(program, arguments);

    myProcess->waitForFinished(-1);

    QString output;

    output = myProcess->readAllStandardError().toStdString().c_str();
}

QStringList MainWindow::parseErrorMessage( const QString &compilerOutpur )
{
    QStringList compilerOutputLines = compilerOutpur.split( "\n" );

    return compilerOutputLines;
}

void MainWindow::checkWorkspace()
{
    QString qstrWorkPath = SettingsManager::Instance()->readSettings( Settings::WORKSPACE_PATH ).toString();
    if( qstrWorkPath.isEmpty() )
    {
        qDebug()<<" WORKSPACE_FILE not found!!";
        WorkspaceDialog workspaceDialog;
        if( workspaceDialog.exec() == QDialog::Accepted )
        {
        }
        else
        {
           qDebug()<<" PATH = "<< SettingsManager::Instance()->readSettings( Settings::WORKSPACE_PATH ).toString();
           setWorkspacePath( SettingsManager::Instance()->readSettings( Settings::WORKSPACE_PATH ).toString() );
        }
    }
//    Thread::msleep(100);
    setWorkspacePath( SettingsManager::Instance()->readSettings( Settings::WORKSPACE_PATH ).toString() );
}

void MainWindow::runCode()
{
    QString program;
    QStringList arguments;

     program = "a.exe";

    QProcess *myProcess = new QProcess(this);
    myProcess->start(program, arguments);

    myProcess->waitForFinished(-1);

    QString output;

    output = myProcess->readAll().toStdString().c_str();
}

void MainWindow::options()
{
    if( ! m_OptionsDialog) {
        m_OptionsDialog = new OptionsDialog( this );
    }
    if( m_OptionsDialog->exec() == QDialog::Accepted )
    {
    }
}

// /////////////// EDITOR SLOTS /////////////////////
void MainWindow::showFileInEditor( QString qstrFileName )
{
    QFile file( qstrFileName );
    QString fileName = file.fileName();
    QFileInfo finfo(fileName);

    if( finfo.isFile())
    {
        if (maybeSave())
        {
            if (!qstrFileName.isEmpty())
                loadFile(qstrFileName);
        }
    }
    qDebug()<< " FINE NAME " << qstrFileName;
}


void MainWindow::openLibrary()
{
    if( ! m_ProgramLibraryDialog) {
        m_ProgramLibraryDialog = new ProgramLibraryDialog( this );
    }
    if( m_ProgramLibraryDialog->exec() == QDialog::Accepted )
    {
    }
}

void MainWindow::addToLibrary()
{
    if( ! m_AddToLibraryWidget) {
        m_AddToLibraryWidget = new AddToLibraryWidget( this );
    }
    if( m_AddToLibraryWidget->exec() == QDialog::Accepted )
    {
    }
}

void MainWindow::setWorkspacePath( QString strPath )
{
    m_fileBrowserWidget->setWorkspacePath( strPath );
}

void MainWindow::initializeEditor()

{

    // codes based from http://eli.thegreenplace.net/2011/04/01/sample-using-qscintilla-with-pyqt/

    initializeFont();

    initializeMargin();

    initializeCaretLine();

    initializeLexer();

    // code based on QSciTE https://code.google.com/p/qscite/

    initializeFolding();

}



void MainWindow::initializeFont()

{

    QFont font("Consolas", 10);

    font.setFixedPitch(true);

    m_codeeditor->setFont(font);

}



void MainWindow::initializeMargin()

{

    QFontMetrics fontmetrics = QFontMetrics(m_codeeditor->font());

    m_codeeditor->setMarginsFont(m_codeeditor->font());

    m_codeeditor->setMarginWidth(0, fontmetrics.width(QString::number(m_codeeditor->lines())) + 6);

    m_codeeditor->setMarginLineNumbers(0, true);

    m_codeeditor->setMarginsBackgroundColor(QColor("#cccccc"));



    connect(m_codeeditor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

}



void MainWindow::onTextChanged()

{

    QFontMetrics fontmetrics = m_codeeditor->fontMetrics();

    m_codeeditor->setMarginWidth(0, fontmetrics.width(QString::number(m_codeeditor->lines())) + 6);
}



void MainWindow::initializeLexer()

{

    QsciLexerCPP *lexer = new QsciLexerCPP();

    lexer->setDefaultFont(m_codeeditor->font());

    lexer->setFoldComments(true);


    m_codeeditor->setLexer(lexer);

}



void MainWindow::initializeCaretLine()

{

    // Current line visible with special background color

    m_codeeditor->setCaretLineVisible(true);

    m_codeeditor->setCaretLineBackgroundColor(QColor("#ffe4e4"));

}



void MainWindow::initializeFolding()

{

    QsciScintilla::FoldStyle state =

            static_cast<QsciScintilla::FoldStyle>((!m_codeeditor->folding()) * 5);

    if (!state)

        m_codeeditor->foldAll(false);

    m_codeeditor->setFolding(state);

}

void MainWindow::showFileToolbar(bool visible)
{
    fileToolBar->setVisible( visible );
}

void MainWindow::showEditToolbar(bool visible)
{
    editToolBar->setVisible( visible );
}

void MainWindow::showBuildToolbar(bool visible)
{
    buildToolBar->setVisible( visible );
}

void MainWindow::showLibToolbar(bool visible)
{
    LibraryToolBar->setVisible( visible );
}

void MainWindow::setShowFileToolbarAct(bool visible)
{
    showFileToolbarAct->setChecked( visible );
}

void MainWindow::setShowEditToolbarAct(bool visible)
{
    showEditToolbarAct->setChecked( visible );
}

void MainWindow::setShowBuildToolbarAct(bool visible)
{
    showBuildToolbarAct->setChecked( visible );
}

void MainWindow::setShowLibToolbarAct(bool visible)
{
    showLibToolbarAct->setChecked( visible );
}
