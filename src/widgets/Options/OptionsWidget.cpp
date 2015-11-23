#include "OptionsWidget.h"
#include "ui_OptionsWidget.h"

OptionsWidget::OptionsWidget(QWidget *parent) :
    QWidget(parent),
    m_ChangeWorkSpaceWidget( nullptr ),
    ui(new Ui::OptionsWidget)
{
    qDebug()<<"0";
    m_ChangeWorkSpaceWidget = new ChangeWorkSpaceWidget( this );
qDebug()<<"1";
    ui->setupUi(this);
qDebug()<<"2";
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    qDebug()<<"3";
    vBoxLayout->setContentsMargins(0,0,0,0);
    qDebug()<<"4";
    vBoxLayout->addWidget(m_ChangeWorkSpaceWidget);
    qDebug()<<"5";
    ui->m_GeneralOptTab->setLayout(vBoxLayout);

    connect(ui->m_OptionsCancelButton,SIGNAL(clicked()),
            this->parent(),SLOT(close()));
}

OptionsWidget::~OptionsWidget()
{
    delete m_ChangeWorkSpaceWidget;
    delete ui;
}
