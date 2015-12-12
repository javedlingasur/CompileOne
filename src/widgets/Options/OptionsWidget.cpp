#include <QSplitter>
#include <QBoxLayout>

#include "OptionsWidget.h"

OptionsWidget::OptionsWidget(QWidget *parent)
    : QWidget( parent )
    , m_optionsListWidget( 0 )
    , m_optiosTabWidget( 0 )
    , m_CompilerOptionsWidget( 0 )
    , m_EditorOptionsWidget( 0 )
{
    m_optionsListWidget = new QListWidget();
    m_optiosTabWidget = new QTabWidget();
    m_optiosTabWidget->setStyleSheet(
                "QTabBar::tab { height: 0px; width: 0px; }" );

    this->setContentsMargins( 1, 1, 1, 1 );
    QSplitter *hSplitter = new QSplitter;
    hSplitter->setFixedWidth( 1 );
    hSplitter->setOrientation( Qt::Horizontal );
    hSplitter->setLineWidth( 1 );
    hSplitter->setHandleWidth( 1 );

    hSplitter->addWidget( m_optionsListWidget );
    hSplitter->addWidget( m_optiosTabWidget );

    QList< int > hList= hSplitter->sizes();
    hList.replace( 0, this->height()/0.8 );
    hList.replace( 1, this->height()/0.2 );
    hSplitter->setSizes( hList );

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setContentsMargins( 0, 0, 0, 0 );
    vBoxLayout->addWidget( hSplitter );

    this->setLayout( vBoxLayout );

    this->setMinimumSize( 500, 400 );

    m_CompilerOptionsWidget = new CompilerOptionsWidget( this );
    addOptions( m_CompilerOptionsWidget->getName(), m_CompilerOptionsWidget );

    m_EditorOptionsWidget = new EditorOptionsWidget;
    addOptions( m_EditorOptionsWidget->getName(), m_EditorOptionsWidget );

    connect( m_optionsListWidget,
             &QListWidget::currentTextChanged,
             this,
             &OptionsWidget::ShowOptions );
}

OptionsWidget::~OptionsWidget()
{

}

void OptionsWidget::addOptions( QString optionName, QWidget *optionWidget )
{
    m_optionsListWidget->addItem( optionName );
    m_optiosTabWidget->addTab( optionWidget, optionName );
}

void OptionsWidget::ShowOptions( QString optionName )
{
    for( unsigned int i = 0 ; i < m_optiosTabWidget->count(); ++ i )
    {
        if( optionName == m_optiosTabWidget->tabText( i ) )
        {
            m_optiosTabWidget->setCurrentIndex( i );
            break;
        }
    }
}
