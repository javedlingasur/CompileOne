#include "SettingsManager.h"
#include <QApplication>

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

void SettingsManager::removeSettings(const QString &key)
{
    m_QSettings->remove( key );
}

bool SettingsManager::hasSettings(const QString &key)
{
    return m_QSettings->value( key ).isNull() ? false : true;
}

