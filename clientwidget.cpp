#include "clientwidget.h"
#include "ui_clientwidget.h"

#include <client/client.h>

ClientWidget::ClientWidget(QWidget *parent) :
	ActionWidgetBase(parent),
	ui(new Ui::ClientWidget)
{
	ui->setupUi(this);
	ui->ip_lineEdit->setInputMask( "000.000.000.000" );
}

ClientWidget::~ClientWidget()
{
	delete ui;
}

int ClientWidget::Execute(ExeContext *context)
{
	client_ = new Client(context);
	return 0;
}
