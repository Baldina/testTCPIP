#ifndef SERVER_H
# define SERVER_H
# include <QObject>
# include <QList>

#include <actions/actionwidgetbase.h>

class QTcpServer;
class QTcpSocket;
class ISocketAdapter;

class Server : public QObject {
  Q_OBJECT
public:
  explicit Server(ExeContext *context, QObject *parent = 0);
public slots:
  void on_newConnection();
  void on_disconnected();
  void on_message(QString);
protected:
  QTcpServer* m_ptcpServer;
  QList<ISocketAdapter*> m_clients;
  quint16 port_;
};

#endif // SERVER_H
