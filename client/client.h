#ifndef MAINWIDGET_H
# define MAINWIDGET_H

# include <QWidget>
#include "actions/actionwidgetbase.h"

namespace Ui {
  class Form;
}

class ISocketAdapter;
class Client : public QObject {

	Q_OBJECT

public:
	explicit Client(ExeContext *context, QObject *parent = 0);

public slots:
	void on_message(QString text);
	void send();

protected:
  ISocketAdapter *sockAdapter_;
  ExeContext *context_;
};

#endif // MAINWIDGET_H
