#ifndef CYCLEWIDGET_H
#define CYCLEWIDGET_H

#include <QWidget>

#include <actions/actionwidgetbase.h>

namespace Ui {
class CycleWidget;
}

class CycleWidget : public ActionWidgetBase
{
	Q_OBJECT

	explicit CycleWidget(QWidget *parent = nullptr); // private

public:
		static CycleWidget * instance() {
			static CycleWidget * _instance = nullptr;
			if ( _instance == nullptr ) {
				_instance = new CycleWidget();
			}
			return _instance;
		}
public:
	~CycleWidget() override;

	int Execute(ExeContext *context) override;

private:
	Ui::CycleWidget *ui;
};

#endif // CYCLEWIDGET_H
