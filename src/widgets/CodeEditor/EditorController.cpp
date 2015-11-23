#include "EditorController.h"

#include "EditorController.h"

EditorController* EditorController::m_pInstance = nullptr;

EditorController* EditorController::Instance()
{
    if (!m_pInstance)
        m_pInstance = new EditorController;

    return m_pInstance;
}

EditorController::EditorController()
{

}

