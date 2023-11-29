#include <QTime>

#include "serverwidget.h"
#include "serverproc.h"
#include "ui_serverwidget.h"
#include "server/server.h"

ServerWidget::ServerWidget(QWidget *parent) :
	ActionWidgetBase(parent),
	ui(new Ui::ServerWidget)
{
	ui->setupUi(this);

	ui->ip_lineEdit->setInputMask( "000.000.000.000" );
	//refreshData();
}


ServerWidget::~ServerWidget()
{
	delete ui;
}

int ServerWidget::Execute(ExeContext *context)
{
	context->port_ = quint16(ui->port_lineEdit->text().toInt());
	server_ = new Server(context);
}

void ServerWidget::refreshWidget()
{
	ui->ip_lineEdit->setText(address_->toString());
	ui->port_lineEdit->setText(QString::number(port_));

}

void ServerWidget::refreshData()
{
	address_->setAddress(ui->ip_lineEdit->text());
	port_ = ui->port_lineEdit->text().toInt();

}

void ServerWidget::on_pushButton_clicked()
{
	refreshData();
}

int ServerWidget::port() const
{
	return port_;
}

QHostAddress *ServerWidget::address() const
{
	return address_;
}
