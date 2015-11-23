#include "OptionsDialog.h"

OptionsDialog::OptionsDialog( QWidget *parent )
                            : QDialog( parent ),
                              m_OptionsWidget( nullptr )
{
    this->setWindowTitle(tr("Options"));
    this->setWindowIcon(QIcon(":/images/options.png"));

    m_OptionsWidget = new OptionsWidget(this);

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setContentsMargins(1,1,1,1);
    vBoxLayout->addWidget(m_OptionsWidget);
    this->setLayout(vBoxLayout);

    this->setMinimumSize(400,300);
}
