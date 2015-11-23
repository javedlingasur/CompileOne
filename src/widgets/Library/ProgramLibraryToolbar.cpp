#include "ProgramLibraryToolbar.h"
#include "ui_ProgramLibraryToolbar.h"

ProgramLibraryToolbar::ProgramLibraryToolbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramLibraryToolbar)
{
    ui->setupUi(this);
}

ProgramLibraryToolbar::~ProgramLibraryToolbar()
{
    delete ui;
}
