#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTableWidget>
#include <QMainWindow>
#include <QVBoxLayout>

//#include <actions/factory.h>

#include "serverwidget.h"
#include "widgetfactory.h"

using namespace std;
namespace Ui {
class MainWindow;
}

class IAction;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void CustomMenuRequested(QPoint pos);
	void RemoveRecord();
	void UpdateModels();
	void EditRecord();
private slots:
	void cellSelected(int, int);
	void cellPressed(int, int);

	void on_actionRun_triggered();

private:
	Ui::MainWindow *ui;
	QVBoxLayout *layout_;
	//ActionFactory *_factory;

	QList<QString> allActions_ = {
		"Client",
		"Server",
		"Send",
		"Receive",
		"Series",
		"End"
	};
	QList<ActionWidgetBase *> scenActions_;
	ExeContext context_;
	WidgetFactory widgetFactory_;

	QList<QString> allPackets_ = {
		"Byte",
		"Array00"
		"Array11"
	};

	void fillTable(QTableWidget* widget, QList<QString> &names);
	// TODO remove this pointer
	QWidget *currentWidget = nullptr;

};

#endif // MAINWINDOW_H
