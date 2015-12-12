#include "FileBrowserWidget.h"
#include "FileBrowserController.h"
#include "../../utility/SettingsManager.h"

#include <QBoxLayout>

FileBrowserWidget::FileBrowserWidget( QWidget *parent )
    : QWidget( parent )
{
    FileBrowserController::Instance();

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setContentsMargins(0,0,0,0);

    m_fileSystemModel = new QFileSystemModel (this );
    QString strWorkPath = SettingsManager::Instance()->readSettings(
                          Settings::WORKSPACE_PATH ).toString();
    m_fileSystemModel->setRootPath( "" );

    m_treeView = new QTreeView( this );
    m_treeView->setModel (m_fileSystemModel );
    m_treeView->setRootIndex( m_fileSystemModel->index( strWorkPath ));
    m_treeView->repaint();
    m_treeView->setAnimated( false );
    m_treeView->setIndentation( 20 );
    m_treeView->setSortingEnabled( true );
    m_treeView->hideColumn( 1 );
    m_treeView->hideColumn( 2 );
    m_treeView->hideColumn( 3 );
    m_treeView->setHeaderHidden( true );
    m_treeView->setSelectionMode( QAbstractItemView::SingleSelection );
    m_treeView->setWindowTitle( QObject::tr( "Dir View" ));
    m_treeView->setGeometry( 0, 22, this->width(), this->height()-22 );
    m_treeView->show();

    vBoxLayout->addWidget( m_treeView  );
    this->setLayout( vBoxLayout );

    connect( m_treeView,
             &QAbstractItemView::doubleClicked,
             this,
             &FileBrowserWidget::selection);
}

void FileBrowserWidget::selection( const QModelIndex& index )
{
    emit showFileInEditor( m_fileSystemModel->filePath( index ) );
}

void FileBrowserWidget::setWorkspacePath( QString strPath )
{
    m_treeView->setRootIndex( m_fileSystemModel->index( strPath ));
    m_treeView->repaint();
}
