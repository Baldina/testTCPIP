#include "cyclewidget.h"
#include "ui_cyclewidget.h"

CycleWidget::CycleWidget(QWidget *parent) :
	ActionWidgetBase(parent),
	ui(new Ui::CycleWidget)
{
	ui->setupUi(this);
}

CycleWidget::~CycleWidget()
{
	delete ui;
}

int CycleWidget::Execute(ExeContext *context)
{

}
