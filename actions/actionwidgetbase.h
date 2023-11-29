#ifndef ACTIONWIDGETBASE_H
#define ACTIONWIDGETBASE_H

#include <QHostAddress>
#include <QTcpSocket>
#include <QWidget>


struct ExeContext;
class Client;
class Server;

class ActionWidgetBase : public QWidget
{
	Q_OBJECT
public:
	explicit ActionWidgetBase(QWidget *parent = nullptr);
	virtual int Execute(ExeContext *context) = 0;

	QString name() const;
	void setName(const QString &name);

private:
	QString name_;
};

struct ExeContext
{
	Client *client_;
	Server *server_;
	QHostAddress address_;
	quint16 port_;
	QTcpSocket *sock_;
	QByteArray *data_;
};

#endif // ACTIONWIDGETBASE_H
