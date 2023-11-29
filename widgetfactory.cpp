#include "widgetfactory.h"

#include "clientwidget.h"
#include "cyclewidget.h"
#include "receivewidget.h"
#include "sendwidget.h"
#include "serverwidget.h"

ActionWidgetBase* WidgetFactory::Create(QString name)
{
	if (name == "Server") {
		return ServerWidget::instance();
	}
	if (name == "Client") {
		return ClientWidget::instance();
	}
	if (name == "Send") {
		return SendWidget::instance();
	}
	if (name == "Receive") {
		return ReceiveWidget::instance();
	}
	if (name == "Series") {
		return CycleWidget::instance();
	}
	return nullptr;
}

void Executor::doWork()
{
	for (auto item: *actList_) {
		item->Execute(context_);
	}
}

Controller::Controller(QList<ActionWidgetBase *> *f, ExeContext *context)
{
	Executor *worker = new Executor(f, context);
	worker->moveToThread(&_thread);
	connect(&_thread, &QThread::started, worker, &Executor::doWork);
	connect(worker, &Executor::finished, &_thread, &QThread::quit);
	connect(worker, &Executor::finished, worker, &Executor::deleteLater);
	connect(&_thread, &QThread::finished, &_thread, &Executor::deleteLater);

	_thread.start();
}

Controller::~Controller() {
	_thread.quit();
	_thread.wait();
}
