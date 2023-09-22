#include "DaWidget.h"
#include <QVariant>

DaWidget::DaWidget(QWidget *parent):
    QWidget{parent}
{
}

bool  DaWidget::setProperty(const char *name, const QVariant &value)
{
    auto  res = QObject::setProperty(name, value);
    emit  propertyChanged(QString(name), value);

    return res;
}

void  DaWidget::compareTriggered(QVariantList data)
{
}
