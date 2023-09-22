#include "Registry.h"

#include <QSettings>
#include <QDataStream>
#include <QDir>
#include <QSet>
#include <QQueue>
#include <QJsonArray>
#include <iostream>
#include <QGuiApplication>
#include <QStyleHints>

namespace Eagle
{
Registry       *Registry::m_instance = nullptr;
std::once_flag  Registry::m_initInstanceFlag;

Registry::Registry()
{
    Qt::ColorScheme  colorScheme = QGuiApplication::styleHints()->colorScheme();

    m_colorScheme = "light";

    if (colorScheme == Qt::ColorScheme::Dark)
    {
        m_colorScheme = "dark";
    }

    qDebug() << "ColorScheme : " << m_colorScheme;
}

QString  Registry::colorSchemeMode() const
{
    return m_colorScheme;
}
}
