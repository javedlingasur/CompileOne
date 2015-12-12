#include "ProgramLibraryWidget.h"

#include <QSplitter>
#include <QBoxLayout>
#include <QTextStream>
#include <QFile>

ProgramLibraryWidget::ProgramLibraryWidget( QWidget *parent )
    : QWidget(parent)
{
    QSplitter *hSplitter = new QSplitter;
    hSplitter->setFixedWidth( 1 );
    hSplitter->setOrientation( Qt::Horizontal );
    hSplitter->setFrameShape( QFrame::Box );
    hSplitter->setLineWidth( 0 );
    hSplitter->setHandleWidth( 1 );

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->setContentsMargins( 0, 0, 0, 0 );

    m_fileSystemModel = new QFileSystemModel( this );
    QString strWorkPath = QDir::currentPath();
    m_fileSystemModel->setRootPath( strWorkPath );

    m_treeView = new QTreeView( this );
    m_treeView->setModel( m_fileSystemModel );
    m_treeView->setRootIndex( m_fileSystemModel->index(
                                  QDir::currentPath() + "/Library" ));
    m_treeView->setAnimated( false );
    m_treeView->setIndentation( 20 );
    m_treeView->setSortingEnabled( true );
    m_treeView->hideColumn( 1 );
    m_treeView->hideColumn( 2 );
    m_treeView->hideColumn( 3 );
    m_treeView->setHeaderHidden( true );
    m_treeView->setSelectionMode( QAbstractItemView::SingleSelection );
    m_treeView->setWindowTitle( QObject::tr( "Dir View" ));
    m_treeView->setGeometry( 0, 22, this->width(), this->height() - 22 );
    m_treeView->show();

    m_progranPreviewText = new QPlainTextEdit();
    m_progranPreviewText->setReadOnly( true );

    hSplitter->addWidget( m_treeView );
    hSplitter->addWidget( m_progranPreviewText );

    QList<int> hList= hSplitter->sizes();
    hList.replace( 0, this->height()/0.8 );
    hList.replace( 1, this->height()/0.2 );
    hSplitter->setSizes( hList );

    hBoxLayout->addWidget( hSplitter );
    this->setLayout( hBoxLayout );

    connect( m_treeView,
             &QAbstractItemView::doubleClicked,
             this,
             &ProgramLibraryWidget::previewSelected);
}

ProgramLibraryWidget::~ProgramLibraryWidget()
{
}

void ProgramLibraryWidget::previewSelected( const QModelIndex& index )
{
    QString strFile = m_fileSystemModel->filePath( index );
    m_progranPreviewText->clear();

    QFile file( strFile );
    file.open( QFile::ReadOnly | QFile::Text );

    QTextStream in( &file );
    QString strFileContent = in.readAll();
    m_progranPreviewText->setPlainText( strFileContent );
}
