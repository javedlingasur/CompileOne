#include "WorkspaceDialog.h"
#include "ui_WorkspaceDialog.h"
#include "../../utility/SettingsManager.h"

#include <QFileDialog>

WorkspaceDialog::WorkspaceDialog( QWidget *parent )
    : QDialog( parent )
    , ui(new Ui::WorkspaceDialog)
{
    ui->setupUi( this );
}

WorkspaceDialog::~WorkspaceDialog()
{
    delete ui;
}

void WorkspaceDialog::on_m_OKButton_clicked()
{
    if( ! ui->m_workspaceLineEdit->text().isEmpty() )
    {
        SettingsManager::Instance()->writeSetting(
                    Settings::WORKSPACE_PATH,
                    ui->m_workspaceLineEdit->text() );
        this->close();
    }
}

void WorkspaceDialog::on_m_BrowseButtonButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(
                this,
                tr("Open Directory"),
                "/home",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );
    if( ! dir.isEmpty() )
    {
        ui->m_workspaceLineEdit->setText( dir );
    }
}
