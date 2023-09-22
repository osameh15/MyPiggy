#ifndef DAELEMENT_H
#define DAELEMENT_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief DaElement class. A Standard element class inherited QObject to use in
 *
 * @author Datall Co, Eagle_Ir
 * @date Apr 2023
 */

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QSequentialIterable>

/**
 * @brief A class representing a DaElement.
 * This class is used to represent a DaElement, which contains an ID, a JSON document,
 * a JSON object, and a map of values.
 * @note The values in the JSON object can be traversed using the traversJson() function.
 */

class DaElement: public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Default constructor.
     * @param parent Optional parent QObject. Default is nullptr.
     */
    explicit DaElement(QObject *parent = nullptr);

    /**
     * @brief Copy constructor.
     * @param da The DaElement to copy from.
     */
    DaElement(const DaElement &da);

    /**
     * @brief Default destructor.
     */
    ~DaElement() = default;

    /**
     * @brief Assignment operator.
     * @param da The DaElement to assign from.
     * @return A reference to the assigned DaElement.
     */
    DaElement&           operator=(const DaElement &da);

    /**
     * @brief Converts the JSON object to a QByteArray.
     * @return A QByteArray representation of the JSON object.
     */
    QByteArray           toJson();

    /**
     * @brief Gets the JSON document.
     * @return The JSON document.
     */
    const QJsonDocument& doc() const;

    /**
     * @brief Sets the JSON document.
     * @param newDoc The new JSON document to set.
     */
    void                 setDoc(const QJsonDocument &newDoc);

    /**
     * @brief Sets the JSON document.
     * @param rawData A QByteArray containing the raw JSON data to set.
     */
    void                 setDoc(const QByteArray rawData);

    /**
     * @brief Gets the ID of the element.
     * @return The ID of the element.
     */
    qint64               id() const;

    /**
     * @brief Sets the ID of the element.
     * @param newId The new ID to set.
     */
    void                 setId(qint64 newId);

    /**
     * @brief Checks whether the element contains a specific key.
     * @param key The key to check for.
     * @return Whether the element contains the specified key.
     */
    bool                 contains(const QString &key);

    /**
     * @brief Retrieves the value of the given key.
     * @tparam T The type of the value to retrieve.
     * @param key The key of the value.
     * @return The value of the specified key.
     */
    template<typename T>
    T                    value(const QString &key) const
    {
        return m_values[key].value<T>();
    }

    /**
     * @brief Retrieves the value of the given key using the array-style syntax.
     * @tparam T The type of the value to retrieve.
     * @param key The key of the value.
     * @return The value of the specified key.
     */
    template<typename T>
    T  operator[](const QString &key) const
    {
        return m_values[key].value<T>();
    }

    /**
     * @brief Retrieves a list of values for the given key.
     * @tparam T The type of the values in the list.
     * @param key The key of the list.
     * @return A list of values for the specified key.
     */
    template<typename T>
    QList<T>  list(const QString &key) const
    {
        QList<T>  tmp;

        if (m_values[key].canConvert(QMetaType(QMetaType::QVariantList)))
        {
            QSequentialIterable  it = m_values[key].value<QSequentialIterable>();

            for (const QVariant &v : it)
            {
                tmp << v.value<T>();
            }

            return tmp;
        }

        return QList<T>();
    }

    /**
     * @brief Set the value of a key in the values map.
     * @param key The key to set.
     * @param value The value to set.
     */
    void               setValue(QString key, QVariant value);

    /**
     * @brief Insert a key-value pair into the values map.
     * @param key The key to insert.
     * @param value The value to insert.
     */
    void               insertValue(QString key, QVariant value);

    /**
     * @brief Get a const reference to the values map.
     * @return The values map.
     */
    const QVariantMap& values() const;

    /**
     * @brief Set the values map.
     * @param newValues The new values map.
     */
    void               setValues(const QVariantMap &newValues);

    /**
     * @brief Update the QJsonDocument object based on the current values map.
     */
    void               updateDoc();

private:
    /**
     * @brief Traverse a QJsonObject and return a QVariantMap representing the same hierarchy.
     *
     * @param json_obj The QJsonObject to be traversed.
     * @return QVariantMap representing the hierarchy of the input QJsonObject.
     */
    QVariantMap        traversJson(QJsonObject json_obj);

    /**
     * @brief Traverse a QVariantMap and return a QJsonObject representing the same hierarchy.
     * @param map The QVariantMap to be traversed.
     * @return QJsonObject representing the hierarchy of the input QVariantMap.
     */
    QJsonObject        traversMap(QVariantMap map);

private:
    /**
     * @brief m_id: The ID of the DaElement.
     */
    qint64  m_id;

    /**
     * @brief m_doc: The JSON document of the DaElement.
     */
    QJsonDocument  m_doc;

    /**
     * @brief m_jsonObject: The JSON object of the DaElement.
     */
    QJsonObject  m_jsonObject;

    /**
     * @brief m_values: A map of values for the DaElement.
     */
    QVariantMap  m_values;
};

/**
 * @brief A smart pointer to DaElement.
 *
 */
typedef QSharedPointer<DaElement> DaElementPtr;

/**
 * @brief A list of smart pointers to DaElement.
 *
 */
typedef QList<DaElementPtr> DaElementsList;

Q_DECLARE_METATYPE(DaElementPtr)
Q_DECLARE_METATYPE(DaElementsList)

#endif // DAELEMENT_H
