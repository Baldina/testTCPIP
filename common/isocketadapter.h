#ifndef ISOCKETADAPTER_H
# define ISOCKETADAPTER_H

# include <QObject>

class ISocketAdapter : public QObject {
	Q_OBJECT

public:
	explicit ISocketAdapter(QObject *parent);
	virtual ~ISocketAdapter();
	virtual void sendString(const QString& str) = 0;
	virtual void sendByteArray(const QByteArray& str) = 0;

signals:
	void message(QString text);
	void disconnected();
	void connected();
};

#endif // ISOCKETADAPTER_H
