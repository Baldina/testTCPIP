#pragma once

#include <QMap>
#include <QObject>
#include <QString>
#include <QThread>

#include "actions/actionwidgetbase.h"

class WidgetFactory
{

public:
	ActionWidgetBase* Create(QString name);
};

class Executor : public QObject
 {
	Q_OBJECT

public:
	Executor(QList<ActionWidgetBase *> *f, ExeContext *context) :
		actList_(f),
		context_(context)
	{

		//std::thread::id this_id = std::this_thread::get_id();
		//std::cout << "thread " << this_id << " sleeping...\n";
	}
	virtual ~Executor(){}

private:
	QList<ActionWidgetBase *> * actList_;
	ExeContext *context_;

public slots:
	void doWork();
signals:
	void finished();
};

 class Controller : public QObject
 {
	Q_OBJECT
	QThread _thread;
 public:
	Controller(QList<ActionWidgetBase *> *f, ExeContext *context);
	~Controller();
 public slots:
 //	void handleResults(const QString &);
 signals:
	void operate(const QString &);
};
