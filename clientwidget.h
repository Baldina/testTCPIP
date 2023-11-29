#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>

#include <actions/actionwidgetbase.h>

#include <client/client.h>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public ActionWidgetBase
{
	Q_OBJECT

	explicit ClientWidget(QWidget *parent = nullptr); // private

public:
		static ClientWidget * instance() {
			static ClientWidget * _instance = nullptr;
			if ( _instance == nullptr ) {
				_instance = new ClientWidget();
			}
			return _instance;
		}
public:
	~ClientWidget();
	virtual int Execute(ExeContext *context) override;

private:
	Ui::ClientWidget *ui;
	Client *client_;
};

#endif // CLIENTWIDGET_H
