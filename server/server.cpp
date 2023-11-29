#include "server.h"
#include "serversocketadapter.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QThread>

Server::Server(ExeContext *context, QObject *parent) :
	QObject(parent),
	m_ptcpServer(new QTcpServer(this)),
	port_(context->port_)
{
  connect(m_ptcpServer, SIGNAL(newConnection()), SLOT(on_newConnection()));

  if (false == m_ptcpServer->listen(QHostAddress::Any, port_)) {
	m_ptcpServer->close();
	throw m_ptcpServer->errorString();
  }
  context->server_ = this;
}

void Server::on_newConnection() {
  QTextStream(stdout) << "new connection" << endl;

  QTcpSocket* pclientSock = m_ptcpServer->nextPendingConnection();
  ISocketAdapter *pSockHandle = new ServerSocketAdapter(pclientSock);

  m_clients.push_back(pSockHandle);

  pSockHandle->sendString("connect");

  connect(pSockHandle, SIGNAL(disconnected()), SLOT(on_disconnected()));
  connect(pSockHandle, SIGNAL(message(QString)), SLOT(on_message(QString)));
}

void Server::on_disconnected() {
  QTextStream(stdout) << "client disconnected" << endl;
  ISocketAdapter* client = static_cast<ServerSocketAdapter*>(sender());
  m_clients.removeOne(client);
  delete client;
}

void Server::on_message(QString msg) {
	foreach (ISocketAdapter *sock, m_clients)
		sock->sendString(msg);
	qDebug() << "Message: " << msg << " Current thread id: " << QThread::currentThreadId();
}


