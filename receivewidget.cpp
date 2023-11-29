#include "receivewidget.h"
#include "ui_receivewidget.h"

ReceiveWidget::ReceiveWidget(QWidget *parent) :
	ActionWidgetBase(parent),
	ui(new Ui::ReceiveWidget)
{
	ui->setupUi(this);
}

ReceiveWidget::~ReceiveWidget()
{
	delete ui;
}

int ReceiveWidget::Execute(ExeContext *context)
{

}
