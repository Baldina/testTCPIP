#include "serverproc.h"

#include <QDateTime>
#include <QTcpSocket>

ServerProc::ServerProc(QHostAddress &addr, quint16 port, QObject *parent) : QTcpServer(parent)
{
	connect(this, &QTcpServer::newConnection, this, &ServerProc::newUser);
	if (!this->listen(QHostAddress::Any, port) && _serverStatus==0) {
		qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(this->errorString());
	} else {
		_serverStatus = 1;
		qDebug() << QString::fromUtf8("Сервер запущен!");
	}
	close();
}

ServerProc::~ServerProc()
{
}

void ServerProc::newUser()
{
	if(_serverStatus == 1) {
//		emit logMessage("New connection", Qt::blue);

		qDebug() << QString::fromUtf8("У нас новое соединение!");
		QTcpSocket* clientSocket = this->nextPendingConnection();

		int idusersocs = static_cast<int>(clientSocket->socketDescriptor());
		_clients[idusersocs] = clientSocket;
		connect(_clients[idusersocs], &QTcpSocket::readyRead,this, &ServerProc::readClient);
	}
}

void ServerProc::readClient()
{
	QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
	int idusersocs = static_cast<int>(clientSocket->socketDescriptor());
	// Пример отправки ответа клиенту
	QTextStream os(clientSocket);
	os.setAutoDetectUnicode(true);
	os << "HTTP/1.0 200 Ok\r\n"
		  "Content-Type: text/html; charset=\"utf-8\"\r\n"
		  "\r\n"
		  "<h1>Nothing to see here</h1>\n"
		  << QDateTime::currentDateTime().toString() << "\n";

	// Полученные данные от клиента выведем в qDebug,
	// можно разобрать данные например от GET запроса и по условию выдавать необходимый ответ.

	qDebug() << clientSocket->readAll()+"\n";

	// Если нужно закрыть сокет
	clientSocket->close();
	_clients.remove(idusersocs);
}

bool ServerProc::doStartServer(QHostAddress addr, quint16 port)
{
	if (!listen(addr, port))
	{
		qDebug() << QObject::tr("Unable to start the server: %1.").arg(errorString());//"Server not started at" << addr << ":" << port;
		close();
		return false;
	}
	qDebug() << "Server started at" << addr << ":" << port;
	return true;
}

bool ServerProc::doStopServer(QHostAddress addr, quint16 port)
{
	if(_serverStatus == 1) {
		foreach(int i, _clients.keys()){
			QTextStream os(_clients[i]);
			os.setAutoDetectUnicode(true);
			os << QDateTime::currentDateTime().toString() << "\n";
			_clients[i]->close();
			_clients.remove(i);
		}
		close();
		qDebug() << QString::fromUtf8("Сервер остановлен!");
		_serverStatus=0;
	}
}
