#ifndef DASTANDARDITEM_H
#define DASTANDARDITEM_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief DaStandardItem class. A Standard item class inherited QObject to use in
 *
 * @author Datall Co, Eagle_Ir
 * @date Apr 2023
 */

#include <QStandardItem>
#include <QObject>
#include <QIcon>
#include <QVariantMap>

class QMenu;
class QAction;

/**
 * @brief The DaStandardItem class is a custom QStandardItem with additional functionality.
 * This class extends the functionality of QStandardItem by adding the ability to set and get a QVariantMap value
 * associated with the item, as well as adding QAction objects to a context menu, inserting separators,
 * hiding/showing all child items and returning the parent item.
 */
class DaStandardItem: public QObject, public QStandardItem
{
    Q_OBJECT

public:
    /**
     * @brief Default constructor for DaStandardItem.
     * @param parent The parent QObject of this item.
     */
    DaStandardItem(QObject *parent = nullptr);

    /**
     * @brief Constructor for DaStandardItem.
     * @param text The text to display in the item.
     * @param parent The parent QObject of this item.
     */
    explicit DaStandardItem(const QString &text, QObject *parent = nullptr);

    /**
     * @brief Constructor for DaStandardItem.
     * @param icon The icon to display in the item.
     * @param text The text to display in the item.
     * @param parent The parent QObject of this item.
     */
    DaStandardItem(const QIcon &icon, const QString &text, QObject *parent = nullptr);

    /**
     * @brief Destructor for DaStandardItem.
     */
    ~DaStandardItem();

    /**
     * @brief Returns the parent QStandardItem of this item.
     * @return A pointer to the parent QStandardItem.
     */
    QStandardItem* parent() const;

    /**
     * @brief Adds an QAction object to the context menu of this item.
     * @param act The QAction object to add.
     */
    void           addAction(QAction *act);

    /**
     * @brief Returns an QAction object with the given text from the context menu of this item.
     * @param text The text of the QAction object to return.
     * @return A pointer to the QAction object with the given text, or nullptr if not found.
     */
    QAction*       action(QString text);

    /**
     * @brief Returns the context menu of this item.
     * @return A pointer to the context menu.
     */
    QMenu*         contextMenu();

    /**
     * @brief Inserts a separator into the context menu of this item.
     */
    void           insertSeparator();

    /**
     * @brief Hides all child items of this item.
     */
    void           hideAll();

    /**
     * @brief Returns the QVariantMap value associated with this item.
     * @return The QVariantMap value.
     */
    QVariantMap    value() const;

    /**
     * @brief Sets the QVariantMap value associated with this item.
     * @param newValue The new QVariantMap value.
     */
    void           setValue(const QVariantMap &value);

public slots:
    /**
     * @brief Reads the state of this object from the given QDataStream.
     * @param in The QDataStream to read from.
     */
    void  read(QDataStream & in);

    /**
     * @brief Writes the state of this object to the given QDataStream.
     * @param out The QDataStream to write to.
     */
    void  write(QDataStream &out) const;

private:
    /**
     * @brief mActions: The list of QAction objects added to the context menu.
     */
    QList<QAction *>  m_actions;
};

#endif // DASTANDARDITEM_H
