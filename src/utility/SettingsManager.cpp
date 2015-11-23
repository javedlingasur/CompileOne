#include "SettingsManager.h"

SettingsManager* SettingsManager::m_pInstance = nullptr;

SettingsManager* SettingsManager::Instance()
{
    if (!m_pInstance)
        m_pInstance = new SettingsManager;

    return m_pInstance;
}

SettingsManager::SettingsManager()
{
    m_strSettingsFile = QApplication::applicationDirPath() + "/compileOne.ini";
    qDebug()<< "Settings Manager Path : "<< m_strSettingsFile;
    m_QSettings = new QSettings( m_strSettingsFile, QSettings::IniFormat );
}

QVariant SettingsManager::readSettings( const QString &key )
{
    return m_QSettings->value( key );
}

void SettingsManager::writeSetting(const QString &key, const QVariant &variant)
{
    m_QSettings->setValue(key, variant);
}
