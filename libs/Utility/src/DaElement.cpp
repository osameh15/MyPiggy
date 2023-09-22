#include "DaElement.h"

DaElement::DaElement(QObject *parent):
    QObject{parent}
{
}

DaElement::DaElement(const DaElement &da)
{
    setValues(da.values());
}

DaElement& DaElement::operator=(const DaElement &da)
{
    setValues(da.values());

    return *this;
}

QByteArray  DaElement::toJson()
{
    m_doc.setObject(traversMap(m_values));

    return m_doc.toJson(QJsonDocument::Compact);
}

const QJsonDocument& DaElement::doc() const
{
    return m_doc;
}

void  DaElement::setDoc(const QJsonDocument &newDoc)
{
    m_doc        = newDoc;
    m_jsonObject = m_doc.object();

    m_values = traversJson(m_jsonObject);
}

void  DaElement::setDoc(const QByteArray rawData)
{
    QJsonDocument  doc = QJsonDocument::fromJson(rawData);

    setDoc(doc);
}

qint64  DaElement::id() const
{
    return m_id;
}

void  DaElement::setId(qint64 newId)
{
    m_id = newId;
}

bool  DaElement::contains(const QString &key)
{
    return m_values.contains(key);
}

void  DaElement::setValue(QString key, QVariant value)
{
    m_values[key] = value;
}

void  DaElement::insertValue(QString key, QVariant value)
{
    m_values.insert(key, value);
}

QVariantMap  DaElement::traversJson(QJsonObject json_obj)
{
    QVariantMap  res;

    for (const QString &key : json_obj.keys())
    {
        QJsonValue  value = json_obj.value(key);

        if (!value.isObject())
        {
            res.insert(key, value.toVariant());
        }
        else
        {
            QVariantMap  tmpMap = traversJson(value.toObject());
            res.insert(key, tmpMap);
        }
    }

    return res;
}

QJsonObject  DaElement::traversMap(QVariantMap map)
{
    QJsonObject  res;
    auto         keys = map.keys();

    for (const QString &key : keys)
    {
        QVariant  value = map.value(key);

        if (!value.canConvert(QMetaType(QMetaType::QVariantMap)))
        {
            res.insert(key, value.toJsonValue());
        }
        else
        {
            QJsonObject  tmpMap = traversMap(value.toMap());
            res.insert(key, tmpMap);
        }
    }

    return res;
}

const QVariantMap& DaElement::values() const
{
    return m_values;
}

void  DaElement::setValues(const QVariantMap &newValues)
{
    m_values = newValues;
}

void  DaElement::updateDoc()
{
    m_doc.setObject(traversMap(m_values));
}
