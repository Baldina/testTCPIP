#include "client.h"
#include "clientsocketadapter.h"

Client::Client(ExeContext *context, QObject *parent) :
	QObject(parent),
	sockAdapter_(new ClientSocketAdapter(this, &context->address_, context->port_)),
	context_(context)
{
	connect(sockAdapter_, &SocketAdapter::message, this, &Client::on_message);
	context->client_ = this;
}

void Client::on_message(QString text) {
	qDebug() << "receive " << text;
}

void Client::send() {
	sockAdapter_->sendString(*(context_->data_));
}
