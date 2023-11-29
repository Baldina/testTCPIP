#include "packetwidget.h"
#include "ui_packetwidget.h"

#include <QFileDialog>

PacketWidget::PacketWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PacketWidget)
{
	ui->setupUi(this);
	connect(ui->selectFileButton, &QPushButton::clicked, this, &PacketWidget::browse);
	ui->label->setFixedWidth(ui->label_4->width());
	ui->label_2->setFixedWidth(ui->label_4->width());
	ui->label_3->setFixedWidth(ui->label_4->width());
	ui->label_4->setFixedWidth(ui->label_4->width());
	ui->label_6->setFixedWidth(ui->label_4->width());
	ui->label_8->setFixedWidth(ui->label_4->width());
}

PacketWidget::~PacketWidget()
{
	delete ui;
}

void PacketWidget::browse()
{
	QString directory = QFileDialog::getExistingDirectory(this,
							tr("Find Files"), QDir::currentPath());

	if (!directory.isEmpty()) {
//		if (directoryComboBox->findText(directory) == -1)
//			directoryComboBox->addItem(directory);
//		directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
	}
}
