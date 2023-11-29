#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QNetworkInterface>

#include <actions/actionwidgetbase.h>

#include <server/server.h>

namespace Ui {
class ServerWidget;
}

class ServerProc;
class ServerWidget : public ActionWidgetBase
{
	Q_OBJECT

	explicit ServerWidget(QWidget *parent = nullptr); // private

public:
		static ServerWidget * instance() {
			static ServerWidget * _instance = nullptr;
			if ( _instance == nullptr ) {
				_instance = new ServerWidget();
			}
			return _instance;
		}

public:
	~ServerWidget() override;

	int Execute(ExeContext *context) override;
	QHostAddress *address() const;

	int port() const;

public slots:
	void refreshWidget();
	void refreshData();

private slots:
	void on_pushButton_clicked();

private:
	Ui::ServerWidget *ui;
	QHostAddress *address_;
	int port_;

	Server *server_;
};

#endif // SERVERWIDGET_H
