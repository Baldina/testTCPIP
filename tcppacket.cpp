#include "tcppacket.h"
#include "ui_tcppacket.h"

TcpPacket::TcpPacket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpPacket)
{
    ui->setupUi(this);
}

TcpPacket::~TcpPacket()
{
    delete ui;
}
