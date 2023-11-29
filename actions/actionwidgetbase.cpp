#include "actionwidgetbase.h"

ActionWidgetBase::ActionWidgetBase(QWidget *parent) : QWidget(parent)
{

}

QString ActionWidgetBase::name() const
{
	return name_;
}

void ActionWidgetBase::setName(const QString &name)
{
	name_ = name;
}
