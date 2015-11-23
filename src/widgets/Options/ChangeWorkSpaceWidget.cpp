#include "ChangeWorkSpaceWidget.h"
#include "ui_ChangeWorkSpaceWidget.h"

ChangeWorkSpaceWidget::ChangeWorkSpaceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeWorkSpaceWidget)
{
	ui->setupUi(this);
    QString strWorkspace = SettingsManager::Instance()->readSettings(SettingsStrings::WORKSPACE_PATH).toString();
    ui->m_WorkspaceLineEdit->setText(strWorkspace);
}

ChangeWorkSpaceWidget::~ChangeWorkSpaceWidget()
{
    delete ui;
}

void ChangeWorkSpaceWidget::on_m_BrowseWorkspaceButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if( ! dir.isEmpty() )
    {
        ui->m_WorkspaceLineEdit->clear();
        ui->m_WorkspaceLineEdit->setText( dir );
    }
}
