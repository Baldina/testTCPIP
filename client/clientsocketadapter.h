#ifndef CLIENTSOCKETADAPTER_H
# define CLIENTSOCKETADAPTER_H

# include "../common/socketadapter.h"

#include <QHostAddress>

class ClientSocketAdapter : public SocketAdapter {
	Q_OBJECT

public:
	explicit ClientSocketAdapter(QObject *parent, QHostAddress *address, quint16 port);

	ClientSocketAdapter(QObject *parent, QString name, quint16 port);

private:
	QHostAddress	*address_;
	quint16			port_;
	QString			name_;
};

#endif // CLIENTSOCKETADAPTER_H
