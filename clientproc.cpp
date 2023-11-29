#include "clientproc.h"

#include <QtCore>
#include <QtNetwork>
#include <QMessageBox>
//#include <QtTest>

Connection::Connection(QHostAddress &addr, int port, QByteArray &data, QObject *parent):
	QObject(parent)
{
	data_ = data;
	address_ = addr;
	port_ = port;
	socket_ = new QTcpSocket;

	connect(socket_, SIGNAL(error(QAbstractSocket::SocketError)),
			this, SLOT(on_error(QAbstractSocket::SocketError)));
	connect(socket_, SIGNAL(connected()), this, SLOT(on_connected()));
	connect(socket_, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
	connect(socket_, SIGNAL(readyRead()), this, SLOT(on_received()));

	socket_->abort();
	isconnected = false;
	timer_ = new QTimer(this);
	connect(timer_, SIGNAL(timeout()), this, SLOT(tmo_check()));
	timer_->start(2000);
	socket_->connectToHost(address_, port);
}

Connection::~Connection()
{
	if (socket_->state() == QAbstractSocket::ConnectedState) {
		socket_->disconnectFromHost();
		socket_->waitForDisconnected(2000);
	}
	delete(socket_);
}

void Connection::tmo_check()
{
	if(!isconnected) {
		emit connection_error((qint32)QAbstractSocket::SocketTimeoutError);
	}
}

void Connection::on_received()
{
	while (socket_->bytesAvailable() > 0)
	{
		QByteArray data = socket_->readAll();
		emit received_data(data);
	}
	socket_->disconnectFromHost();
}

void Connection::on_connected()
{
	emit device_connected();
	socket_->write(data_.data(), data_.size()); //write size of data
	isconnected = true;
}

void Connection::on_disconnected()
{
//	emit device_disconnected();
	isconnected = false;
	deleteLater();
}

void Connection::on_error(QAbstractSocket::SocketError sock_error)
{
	switch (sock_error) {
	case QAbstractSocket::RemoteHostClosedError:
		qDebug() << "The host was not found. Please check the host name and port settings." << socket_->errorString();
		break;
	case QAbstractSocket::HostNotFoundError:
		qDebug() << "The host was not found. Please check the host name and port settings." << socket_->errorString();
		break;
	case QAbstractSocket::ConnectionRefusedError:
		qDebug() << "The connection was refused by the peer. Make sure the fortune server is running, "
									"and check that the host name and port "
									"settings are correct."  << socket_->errorString();
		break;
	default:
		qDebug() << "The following error occurred: %1." << socket_->errorString() << address_;
	}
	emit connection_error(sock_error);
	return;
}
