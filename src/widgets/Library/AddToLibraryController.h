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
#pragma once

#include <string>

enum FileOperations
{
    FILE_ALREADY_EXIST = 0,
    FILE_SAVED_SUCCESSFULLY = 1,
    FILE_COULD_NOT_BE_CREATED = 2,
    FILE_OPERATION_DEFAULT = -1
};

class AddToLibraryController
{
public:
    static AddToLibraryController* Instance();

    FileOperations AddToLibrary( std::string strName,
                                 std::string strFilePath );
private:
    AddToLibraryController();

    AddToLibraryController( AddToLibraryController const& ){}

    AddToLibraryController& operator=( AddToLibraryController const& ){}

    static AddToLibraryController* m_pInstance;
};


