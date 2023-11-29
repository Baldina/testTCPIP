#ifndef RECEIVEWIDGET_H
#define RECEIVEWIDGET_H

#include <QWidget>

#include <actions/actionwidgetbase.h>

namespace Ui {
class ReceiveWidget;
}

class ReceiveWidget : public ActionWidgetBase
{
	Q_OBJECT

	explicit ReceiveWidget(QWidget *parent = nullptr); // private

public:
		static ReceiveWidget* instance() {
			static ReceiveWidget * _instance = nullptr;
			if ( _instance == nullptr ) {
				_instance = new ReceiveWidget();
			}
			return _instance;
		}

public:
	~ReceiveWidget() override;

	int Execute(ExeContext *context) override;

private:
	Ui::ReceiveWidget *ui;
};

#endif // RECEIVEWIDGET_H
