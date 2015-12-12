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

#include "ErrorOutputWidget.h"

#include <QBoxLayout>

namespace Co {
namespace Output {

ErrorOutputWidget::ErrorOutputWidget()
    : m_errorListView( 0 )
{
    m_errorListView = new QListView( this );

    m_errorListView->setFrameStyle( QFrame::NoFrame );
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setContentsMargins( 0, 0, 0, 0 );
    vBoxLayout->addWidget( m_errorListView );

    this->setLayout( vBoxLayout );
}

ErrorOutputWidget::~ErrorOutputWidget()
{

}

}
}
