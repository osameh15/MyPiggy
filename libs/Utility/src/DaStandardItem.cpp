#include "DaStandardItem.h"

#include <QAction>
#include <QMenu>

DaStandardItem::DaStandardItem(QObject *parent):
    QObject(parent), QStandardItem()
{
}

DaStandardItem::DaStandardItem(const QString &text, QObject *parent):
    QObject(parent), QStandardItem(text)
{
}

DaStandardItem::DaStandardItem(const QIcon &icon, const QString &text, QObject *parent):
    QObject(parent), QStandardItem(icon, text)
{
}

DaStandardItem::~DaStandardItem()
{
}

QStandardItem * DaStandardItem::parent() const
{
    return QStandardItem::parent();
}

void  DaStandardItem::addAction(QAction *act)
{
    m_actions.append(act);
}

QAction * DaStandardItem::action(QString text)
{
    for (auto act : m_actions)
    {
        if (act->text() == text)
        {
            return act;
        }
    }

    return nullptr;
}

QMenu * DaStandardItem::contextMenu()
{
    auto  menu = new QMenu();

    for (auto act : m_actions)
    {
        menu->addAction(act);
    }

    return menu;
}

void  DaStandardItem::insertSeparator()
{
    auto  action = new QAction();

    action->setSeparator(true);

    m_actions.append(action);
}

void  DaStandardItem::hideAll()
{
    for (auto act : m_actions)
    {
        if (!act->isSeparator())
        {
            act->setVisible(false);
        }
    }
}

QVariantMap  DaStandardItem::value() const
{
    if (data(999).isNull())
    {
        return QVariantMap();
    }

    return data(999).toMap();
}

void  DaStandardItem::setValue(const QVariantMap &value)
{
    setData(value, 999);
}

void  DaStandardItem::read(QDataStream &in)
{
    QStandardItem::read(in);

    QVariantMap  temp;

    in >> temp;
    setValue(temp);
}

void  DaStandardItem::write(QDataStream &out) const
{
    if (!this->parent())
    {
        return;
    }

    out << (dynamic_cast<DaStandardItem *>(this->parent()))->value().value("label").toString();

    if (out.status() == QDataStream::WriteFailed)
    {
        return;
    }

    QStandardItem::write(out);

    out << value();
}
