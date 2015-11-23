#include "AddToLibraryController.h"

AddToLibraryController* AddToLibraryController::m_pInstance = nullptr;

AddToLibraryController* AddToLibraryController::Instance()
{
    if (!m_pInstance)
        m_pInstance = new AddToLibraryController;

    return m_pInstance;
}

AddToLibraryController::AddToLibraryController()
{

}

FileOperations AddToLibraryController::AddToLibrary( std::string strName,
                                                     std::string strFilePath)
{
    std::string strLibPath = SettingsManager::Instance()->
                             readSettings(SettingsStrings::WORKSPACE_PATH).toString().toStdString();

    strLibPath = strLibPath + "/" + strName + ".cpp";

    if( std::ifstream( strLibPath ) )
    {
        return FileOperations::FILE_ALREADY_EXIST;
    }
    std::ofstream file(strLibPath);

    if( file )
    {
        return FileOperations::FILE_SAVED_SUCCESSFULLY;
    }
    else
    {
        return FileOperations::FILE_COULD_NOT_BE_CREATED;
    }
}
