#include "tcpheader.h"
#include "ui_tcpheader.h"

TcpHeader::TcpHeader(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TcpHeader)
{
	ui->setupUi(this);
}

TcpHeader::~TcpHeader()
{
	delete ui;
}
