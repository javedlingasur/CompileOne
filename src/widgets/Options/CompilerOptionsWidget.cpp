/***************************************************************************
*Copyright (c) 2015 Javed Lingasur
*
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all
*copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*SOFTWARE.
***************************************************************************/

#include "CompilerOptionsWidget.h"
#include "ui_CompilerOptionsWidget.h"

#include <QDebug>
#include <QFileDialog>

#include "utility/SettingsManager.h"

CompilerOptionsWidget::CompilerOptionsWidget( QWidget *parent )
    : QWidget(parent)
    , ui(new Ui::CompilerOptionsWidget)
{
    ui->setupUi( this );

    if( SettingsManager::Instance()->hasSettings( Settings::COMPILER_PATH ))
    {
        QString compiler = SettingsManager::Instance()->readSettings(
                    Settings::COMPILER_PATH ).toString();
        ui->m_compilerLineEdit->setText( compiler );
        qDebug()<< "COMPILER :"<<compiler;
    }
}

CompilerOptionsWidget::~CompilerOptionsWidget()
{
    delete ui;
}

void CompilerOptionsWidget::on_m_compilerSelectBtn_clicked()
{
    QString file = QFileDialog::getOpenFileName( this,
                                                 tr("Compiler"),
                                                 "/home",
                                                 "*" );
    if( ! file.isEmpty() )
    {
        ui->m_compilerLineEdit->setText( file );
    }
}

void CompilerOptionsWidget::on_m_compilerLineEdit_returnPressed()
{
    if( !ui->m_compilerLineEdit->text().isEmpty() )
    {
        SettingsManager::Instance()->writeSetting(
                    Settings::COMPILER_PATH,
                    ui->m_compilerLineEdit->text() );
    }
}
