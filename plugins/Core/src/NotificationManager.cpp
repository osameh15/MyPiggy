#include "NotificationManager.h"
#include "QWaitingSpinner.h"

#include <QAction>
#include <QPen>
#include <qosdnotification.h>
#include <qosdnotificationmanager.h>

namespace Eagle
{
namespace Notify
{
NotificationManager *NotificationManager::m_instance = nullptr;

std::once_flag  NotificationManager::initInstanceFlag;

NotificationManager::NotificationManager()

{
    m_OSDManager = new QOSDNotificationManager;
    m_OSDManager->setMaxCount(5);
}

QWaitingSpinner * NotificationManager::showProgressBar(QWidget *parent)
{
    if (!m_spinner)
    {
        m_spinner = new QWaitingSpinner(parent);

        m_spinner->setRoundness(70.0);
        m_spinner->setMinimumTrailOpacity(15.0);
        m_spinner->setTrailFadePercentage(70.0);
        m_spinner->setNumberOfLines(12);
        m_spinner->setLineLength(10);
        m_spinner->setLineWidth(5);
        m_spinner->setInnerRadius(10);
        m_spinner->setRevolutionsPerSecond(1);
        m_spinner->setColor(QColor(0, 188, 176));
        m_spinner->start();
    }

    return m_spinner;
}

void  NotificationManager::stopProgressBar(QWidget *parent)
{
    if (!m_spinner)
    {
        return;
    }

    if (m_spinner->parentWidget() == parent)
    {
        m_spinner->stop();
        m_spinner->deleteLater();
        m_spinner = nullptr;
    }
}

void  NotificationManager::showStatusBarMessage(QString msg, int timeout)
{
    emit  statusBarDisplay(msg, timeout);
}

void  NotificationManager::showOSDNotify(QString title, QString description, int type, int duration)
{
    QPen  pen;

    switch (type)
    {
    case Notify::Information:
    {
        pen.setColor(Qt::green);

        break;
    }
    case Notify::Warning:
    {
        pen.setColor(Qt::yellow);

        break;
    }
    case Notify::Critical:
    {
        pen.setColor(Qt::red);

        break;
    }
    default:
        break;
    }

    if (m_OSDManager)
    {
        pen.setStyle(Qt::SolidLine);

        pen.setWidth(2);

        QPen  hoverPen(pen);

        hoverPen.setStyle(Qt::DashLine);

        QOSDNotification *notification = new QOSDNotification(title, description);

        notification->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

        notification->setBorderPen(pen);

        notification->setBorderHoverPen(hoverPen);

        notification->setDuration(duration);

        m_OSDManager->add(notification);
    }
}

std::pair<bool, QString>  NotificationManager::showInputDialog(QWidget *parent, const QString &title, const QString &label, const QString &text,
                                                               QLineEdit::EchoMode echo, Qt::WindowFlags flags, Qt::InputMethodHints inputMethodHints)
{
    QInputDialog *dialog(new QInputDialog(parent, flags));

    dialog->setWindowTitle(title);
    dialog->setLabelText(label);
    dialog->setTextValue(text);
    dialog->setTextEchoMode(echo);
    dialog->setInputMethodHints(inputMethodHints);
    dialog->resize(QSize(300, 200));

    const int  ret = dialog->exec();

    if (ret)
    {
        auto  inputText = dialog->textValue();

        delete dialog;

        return std::make_pair(true, inputText);
    }

    delete dialog;

    return std::make_pair(false, QString());
}

QMessageBox * NotificationManager::showMessageBox(const QString &title, const QString &text, QMessageBox::Icon icon, QWidget *parent,
                                                  QMessageBox::StandardButtons buttons, Qt::WindowFlags flags)
{
    return new QMessageBox(icon, title, text, buttons, parent, flags);
}
}
}
