#ifndef SENDWIDGET_H
#define SENDWIDGET_H

#include <QWidget>

#include <actions/actionwidgetbase.h>

namespace Ui {
class SendWidget;
}

class SendWidget : public ActionWidgetBase
{
	Q_OBJECT

	explicit SendWidget(QWidget *parent = nullptr); // private

public:
		static SendWidget * instance() {
			static SendWidget * _instance = nullptr;
			if ( _instance == nullptr ) {
				_instance = new SendWidget();
			}
			return _instance;
		}

public:
	~SendWidget() override;

	int Execute(ExeContext *context) override;

private:
	Ui::SendWidget *ui;
};

#endif // SENDWIDGET_H
