#ifndef SERVERPROCESS_H
#define SERVERPROCESS_H

#include <QColor>
#include <QObject>
#include <QTcpServer>
#include <QThread>

/* This file contains Worker and Controller classes to run ServerProc in another thread */

class ServerProc : public QTcpServer
{
	Q_OBJECT

public:
	explicit ServerProc(QHostAddress &addr, quint16 port, QObject *parent = nullptr);
	~ServerProc();

signals:
	void logMessage(QString log, QColor color);

public slots:
	void newUser();
	void readClient();
	bool doStartServer(QHostAddress addr, quint16 port);
	bool doStopServer(QHostAddress addr, quint16 port);

private:
	int _serverStatus;
	QMap<int, QTcpSocket *> _clients;
};

#endif // SERVERPROCESS_H
