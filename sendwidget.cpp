#include "sendwidget.h"
#include "ui_sendwidget.h"

SendWidget::SendWidget(QWidget *parent) :
	ActionWidgetBase(parent),
	ui(new Ui::SendWidget)
{
	ui->setupUi(this);
}

SendWidget::~SendWidget()
{
	delete ui;
}

int SendWidget::Execute(ExeContext *context)
{

}
