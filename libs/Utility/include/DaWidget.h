#ifndef DWIDGET_H
#define DWIDGET_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief DaWidget class. A Standard widget class inherited QWidget to use in
 *
 * @author Datall Co, Eagle_Ir
 * @date May 2023
 */

#include <QWidget>
#include <QLatin1String>

/**
 * @brief Custom widget class for DaWidget.
 * This class represents a custom widget derived from QWidget. It provides additional functionality and signals related to
 * properties and serialization.
 */
class DaWidget: public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Explicit constructor for DaWidget.
     * @param parent The parent widget.
     */
    explicit DaWidget(QWidget *parent = nullptr);

    /**
     * @brief Set the title of the widget.
     * @param title The title to set for the widget.
     */
    void                setTitle(QString title);

    /**
     * @brief Set a property value.
     * This function sets the value of a property with the given name.
     * @param name The name of the property.
     * @param value The new value to set for the property.
     * @return True if the property was set successfully, false otherwise.
     */
    virtual bool        setProperty(const char *name, const QVariant &value);

    /**
     * @brief Specifies the object parent for the widget.
     * This pure virtual function is used to set the parent widget for the object. The derived classes should provide an implementation that assigns the specified
     *`widget` as the parent for the object. The parent widget is responsible for managing the memory and lifetime of the object.
     * @param widget A pointer to the parent QWidget object.
     */
    virtual void        setObjectParent(QWidget *widget) = 0;

    /**
     * @brief Serialize the widget.
     * This function should be overridden by derived classes to serialize the widget's data into a QByteArray.
     * @return The serialized data as a QByteArray.
     */
    virtual QByteArray  serialize() = 0;

    /**
     * @brief Deserialize the widget.
     * This function should be overridden by derived classes to deserialize the widget's data from a QByteArray.
     * @param data The serialized data as a QByteArray.
     */
    virtual void        deSerialize(QByteArray data) = 0;

    /**
     * @brief Virtual function for handling a compare action triggered event.
     * This virtual function is meant to be overridden by derived classes to handle a compare
     * action triggered event. It receives a @c QVariantMap @p data that may contain relevant
     * information for the compare action.
     * @param data A @c QVariantList containing data related to the compare action.
     */
    virtual void        compareTriggered(QVariantList data);

signals:
    /**
     * @brief Signal emitted when a property is changed.
     * This signal is emitted when a property with a specific key is changed, along with the new value of the property.
     * @param key The key of the changed property.
     * @param value The new value of the property.
     */
    void                propertyChanged(QString key, QVariant value);
};

#endif // DWIDGET_H
