#include "FileBrowserWidget.h"
#include "FileBrowserController.h"

FileBrowserWidget::FileBrowserWidget( QWidget *parent )
{
    FileBrowserController::Instance();

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setContentsMargins(1,1,1,1);

    m_fileSystemModel = new QFileSystemModel(this);
    QString strWorkPath = SettingsManager::Instance()->readSettings( Settings::WORKSPACE_PATH ).toString();
    qDebug()<<"strWorkPath " <<strWorkPath;
//    if( strWorkPath.isEmpty())
//    {
//        qDebug()<<"1";
        m_fileSystemModel->setRootPath("");
//    }

    m_treeView = new QTreeView(this);
    m_treeView->setModel(m_fileSystemModel);
    m_treeView->setRootIndex( m_fileSystemModel->index( strWorkPath ));
    m_treeView->repaint();
    m_treeView->setAnimated(false);
    m_treeView->setIndentation(20);
    m_treeView->setSortingEnabled(true);
    m_treeView->hideColumn(1);
    m_treeView->hideColumn(2);
    m_treeView->hideColumn(3);
    m_treeView->setHeaderHidden(true);
    m_treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_treeView->setWindowTitle(QObject::tr("Dir View"));
    m_treeView->setGeometry(0,22,this->width(),this->height()-22);
    m_treeView->show();

    m_treeView->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn);
    m_treeView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn);

    vBoxLayout->addWidget(m_treeView);
    this->setLayout(vBoxLayout);

//    setWorkspacePath( strWorkPath );

    connect(m_treeView, SIGNAL(doubleClicked(const QModelIndex&)),
                 this, SLOT(selection(const QModelIndex&) ));
}

void FileBrowserWidget::selection(const QModelIndex& index)
{
    qDebug(m_fileSystemModel->filePath( index ).toStdString().c_str());
    qDebug(index.data().toString().toStdString().c_str());
    emit showFileInEditor( m_fileSystemModel->filePath( index ) );
}

void FileBrowserWidget::setWorkspacePath( QString strPath )
{
    qDebug()<<"FileBrowsewrComponent :" << strPath;
    m_treeView->setRootIndex( m_fileSystemModel->index( strPath ));
    m_treeView->repaint();
}
