#include "FileBrowserController.h"

FileBrowserController* FileBrowserController::m_pInstance = nullptr;

FileBrowserController* FileBrowserController::Instance()
{
    if ( !m_pInstance )
        m_pInstance = new FileBrowserController;

    return m_pInstance;
}

FileBrowserController::FileBrowserController()
{

}
