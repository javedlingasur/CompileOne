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
#ifndef WORKSPACEDIALOG_H
#define WORKSPACEDIALOG_H

#include <QDialog>
#include "../../common/QtIncludes.h"
#include "../../utility/SettingsManager.h"

namespace Ui {
class WorkspaceDialog;
}

class WorkspaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorkspaceDialog(QWidget *parent = 0);
    ~WorkspaceDialog();

private slots:
    void on_m_OKButton_clicked();

    void on_m_BrowseButtonButton_clicked();

private:
    Ui::WorkspaceDialog *ui;
};

#endif // WORKSPACEDIALOG_H