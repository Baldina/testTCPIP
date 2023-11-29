#include "clientsocketadapter.h"
#include <QVector>
#include <QTcpSocket>
#include <QDataStream>

ClientSocketAdapter::ClientSocketAdapter(QObject *parent, QHostAddress *address, quint16 port)
  : SocketAdapter(parent),
	address_(address),
	port_(port)
{
	m_ptcpSocket->connectToHost(*address, port);
	// we need to wait...
	if(!m_ptcpSocket->waitForConnected(5000))
	{
		qDebug() << "Error: " << m_ptcpSocket->errorString();
	}
}

ClientSocketAdapter::ClientSocketAdapter(QObject *parent, QString name, quint16 port)
  : SocketAdapter(parent),
	port_(port),
	name_(name)
{
	m_ptcpSocket->connectToHost(name_, port);
}
