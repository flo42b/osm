/**
 *  OSM
 *  Copyright (C) 2019  Pavel Smokotnin

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "settings.h"
#include "workingfolder.h"

QSettings *Settings::m_settings = nullptr;

Settings::Settings(const QString &group, QObject *parent) : QObject(parent), m_group(group)
{
    if (!m_settings) {
        Settings::m_settings = new QSettings(
            workingfolder::settingsFilePath(),
            QSettings::IniFormat
        );
    }
}
void Settings::setValue(const QString &key, const QVariant &value)
{
    group_guard guard(m_group);
    m_settings->setValue(key, value);
}
void Settings::copyGroup(const QString &sourceGroupName, const QString &destinationGroupName)
{
    group_guard guard(m_group);
    QStringList keys = m_settings->allKeys();
    QString sourceGroupNameStr = sourceGroupName;
    QString destinationKey;
    QVariant sourceValue;
    for(const QString& i : keys){
        if(i.startsWith(sourceGroupName)){
            sourceValue = m_settings->value(i);
            destinationKey = destinationGroupName + i.mid(sourceGroupNameStr.length());
            m_settings->setValue(destinationKey, sourceValue);
        }
    }
    m_settings->sync();
}
void Settings::removeGroup(const QString &sourceGroupName)
{
    group_guard guard(m_group);
    m_settings->remove(sourceGroupName);
    m_settings->sync();
}
QVariant Settings::value(const QString &key, const QVariant &defaultValue)
{
    group_guard guard(m_group);
    QVariant value = m_settings->value(key);
    if (value == QVariant::Invalid && defaultValue != QVariant::Invalid) {
        m_settings->setValue(key, defaultValue);
        value = m_settings->value(key);
    }
    return value;
}
Settings *Settings::getGroup(const QString &groupName)
{
    return new Settings(groupName, this);
}

Settings *Settings::getSubGroup(const QString &groupName)
{
    return getGroup(m_group + groupName);
}
QStringList Settings::allKeys()
{
    group_guard guard(m_group);
    QStringList keylist = m_settings->allKeys();
    return keylist;
}
QStringList Settings::getChildGroups()
{
    group_guard guard(m_group);
    QStringList childGroups = m_settings->childGroups();
    return childGroups;
}
void Settings::flush()
{
    m_settings->sync();
}
