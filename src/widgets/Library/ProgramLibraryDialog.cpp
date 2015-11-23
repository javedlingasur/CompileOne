#include "ProgramLibraryDialog.h"

ProgramLibraryDialog::ProgramLibraryDialog( QWidget *parent )
                            : QDialog( parent ),
                              m_ProgramLibraryWidget( nullptr ),
                              m_ProgramLibraryToolbar( nullptr )
{
    this->setWindowTitle(tr("Program Library"));
    this->setWindowIcon(QIcon(":/images/programLibrary.png"));

    m_ProgramLibraryToolbar = new ProgramLibraryToolbar( this );
    m_ProgramLibraryWidget = new ProgramLibraryWidget( this );

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setContentsMargins(1,1,1,1);
    vBoxLayout->addWidget(m_ProgramLibraryToolbar);
    vBoxLayout->addWidget(m_ProgramLibraryWidget);
    this->setLayout(vBoxLayout);

    this->setMinimumSize(400,300);
}
