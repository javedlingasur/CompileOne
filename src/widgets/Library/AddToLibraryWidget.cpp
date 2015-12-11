#include "AddToLibraryWidget.h"
#include "ui_AddToLibraryWidget.h"

AddToLibraryWidget::AddToLibraryWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddToLibraryWidget)
{
    ui->setupUi(this);
}

AddToLibraryWidget::~AddToLibraryWidget()
{
    delete ui;
}

void AddToLibraryWidget::on_m_CancelButton_clicked()
{
    this->close();
}

void AddToLibraryWidget::on_m_BrowseButton_clicked()
{
    QString qstrWorkPath = SettingsManager::Instance()->readSettings( Settings::WORKSPACE_PATH ).toString();

    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setDirectory( QDir(qstrWorkPath));
    dialog.exec();
    QStringList files = dialog.selectedFiles();

    if( ! files.isEmpty() )
    {
        ui->m_BrowseLineEdit->setText(files[0]);
    }
}

void AddToLibraryWidget::on_m_AddButton_clicked()
{
    if( ui->m_DispleyNameLineEdit->text().isEmpty() )
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning...");
        msgBox.setText("Please enter the program name to be displayed in the library...");
        msgBox.exec();
        return;
    }
    if( ui->m_BrowseLineEdit->text().isEmpty() )
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning...");
        msgBox.setText("Please select the file to be added to library...");
        msgBox.exec();
        return;
    }

    FileOperations retFileOperation;

    retFileOperation = AddToLibraryController::Instance()->AddToLibrary(
                ui->m_DispleyNameLineEdit->text().toStdString(),
                ui->m_BrowseLineEdit->text().toStdString() );

    switch(retFileOperation)
    {
    case FileOperations::FILE_ALREADY_EXIST :
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error...");
        msgBox.setText("File name already exist. Please select different name...");
        msgBox.exec();
        break;
    }
    case FileOperations::FILE_SAVED_SUCCESSFULLY :
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Success...");
        msgBox.setText("Selected file is added to library...");
        msgBox.exec();
        this->close();
        break;
    }
    case FileOperations::FILE_COULD_NOT_BE_CREATED :
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error...");
        msgBox.setText("Error occured while saving the file...");
        msgBox.exec();
        this->close();
        break;
    }
    default:
        break;
    }

}
