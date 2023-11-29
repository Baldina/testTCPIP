#ifndef CONNECTION_H
#define CONNECTION_H

#include <QHostAddress>
#include <QtNetwork>

class Connection : public QObject
{
	Q_OBJECT

public:
	Connection(QHostAddress &addr, int port, QByteArray &data, QObject *parent = 0);
	~Connection();

public slots:
	void on_received();
	void on_error(QAbstractSocket::SocketError sock_error);
	void on_connected();
	void on_disconnected();
	void tmo_check();
//	void on_send_to_device(qint64 bytes);

signals:
	void received_data(QByteArray &data);
	void device_connected();
	void device_disconnected();
	void connection_error(qint32 code);
//	void send_to_device(qint64 bytes);

public:
	void cconnect(QHostAddress &addr, int port);
	void cdisconnect();

private:
	QTcpSocket *socket_;
	QHostAddress address_;
	QByteArray data_;
	int port_;
	QTimer *timer_;
	bool isconnected;

private:
	//bool send(QByteArray &data);
	//QByteArray IntToArray(qint32 source); //Use qint32 to ensure that the number have 4 bytes
};
#endif // CONNECTION_H
