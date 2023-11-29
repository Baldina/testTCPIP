#include <QMessageBox>
#include <iostream>
#include "mainwindow.h"
#include "tcpheader.h"
//#include "actions/actionbase.h"
//#include "actions/factory.h"
#include "ui_mainwindow.h"

#define trUtf8
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setWindowTitle("InfNetTest");
	ui->actionTableWidget->setColumnCount(1);
	ui->actionTableWidget->setShowGrid(true);
	ui->actionTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->actionTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->actionTableWidget->horizontalHeader()->setStretchLastSection(true);
	ui->actionTableWidget->verticalHeader()->hide();
	ui->actionTableWidget->horizontalHeader()->hide();
	ui->actionTableWidget->setDragDropMode(QAbstractItemView::DragOnly);

	ui->scenarioTableWidget->setDragDropMode(QAbstractItemView::DropOnly);
	ui->scenarioTableWidget->setColumnCount(2);
	ui->scenarioTableWidget->setShowGrid(true);
	ui->scenarioTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->scenarioTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->scenarioTableWidget->horizontalHeader()->setStretchLastSection(true);
	ui->scenarioTableWidget->setHorizontalHeaderLabels(QStringList() << tr("Scenario") << tr("Description"));
	ui->scenarioTableWidget->verticalHeader()->hide();
	connect( ui->scenarioTableWidget, &QTableWidget::cellClicked, this, &MainWindow::cellSelected );
	connect( ui->scenarioTableWidget, &QTableWidget::cellPressed, this, &MainWindow::cellPressed );
//	connect(ui->scenarioTableWidget->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
//			this, SLOT(onRowChange(QModelIndex,QModelIndex)), Qt::QueuedConnection);

	ui->packet1TableWidget->setColumnCount(1);
	ui->packet1TableWidget->setShowGrid(true);
	ui->packet1TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->packet1TableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->packet1TableWidget->horizontalHeader()->setStretchLastSection(true);
	ui->packet1TableWidget->verticalHeader()->hide();
	ui->packet1TableWidget->horizontalHeader()->hide();
	ui->packet1TableWidget->setDragDropMode(QAbstractItemView::DragOnly);
	// Устанавливаем Контекстное Меню
	ui->packet1TableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	// Подключаем СЛОТ вызова контекстного меню
	connect(ui->packet1TableWidget, SIGNAL(customContextMenuRequested(QPoint)),
			this, SLOT(CustomMenuRequested(QPoint)));

	//QTextStream *textStream = new QTextStream (stdout);
	//_factory = new ActionFactory(*textStream);

	// TODO get list of operations from ActionFactory
	fillTable(ui->actionTableWidget, allActions_);
	fillTable(ui->packet1TableWidget, allPackets_);
//	fillActions(names);
}

MainWindow::~MainWindow()
{
//	delete(_factory);
	delete ui;
}

void MainWindow::CustomMenuRequested(QPoint pos)
{
	/* Создаем объект контекстного меню */
	QMenu * menu = new QMenu(this);
	/* Создаём действия для контекстного меню */
	QAction * editDevice = new QAction(trUtf8("Редактировать"), this);
	QAction * deleteDevice = new QAction(trUtf8("Удалить"), this);
	/* Подключаем СЛОТы обработчики для действий контекстного меню */
	connect(editDevice, SIGNAL(triggered()), this, SLOT(EditRecord()));     // Обработчик вызова диалога редактирования
	connect(deleteDevice, SIGNAL(triggered()), this, SLOT(RemoveRecord())); // Обработчик удаления записи
	/* Устанавливаем действия в меню */
	menu->addAction(editDevice);
	menu->addAction(deleteDevice);
	/* Вызываем контекстное меню */
	menu->popup(ui->packet1TableWidget->viewport()->mapToGlobal(pos));
}

/* Слот обновления модели представления данных
 * */
void MainWindow::UpdateModels()
{
//    ui->packet1TableWidget->model()->select();
	ui->packet1TableWidget->resizeColumnsToContents();
}

/* Метод для активации диалога добавления записей в режиме редактирования
 * с передачей индекса выбранной строки
 * */
void MainWindow::EditRecord()
{
	ui->packet1TableWidget->insertRow ( ui->packet1TableWidget->rowCount() );
	ui->packet1TableWidget->setItem   ( ui->packet1TableWidget->rowCount()-1, 0,
							 new QTableWidgetItem("new"));
}
/* Слот для удаления записи из таблицы
 * */
void MainWindow::RemoveRecord()
{
	/* Выясняем, какая из строк была выбрана
	 * */
	int row = ui->packet1TableWidget->selectionModel()->currentIndex().row();
	/* Проверяем, что строка была действительно выбрана
	 * */
	if(row >= 0){
		/* Задаём вопрос, стоит ли действительно удалять запись.
		 * При положительном ответе удаляем запись
		 * */
		if (QMessageBox::warning(this,
								 trUtf8("Удаление записи"),
								 trUtf8("Вы уверены, что хотите удалить эту запись?"),
								 QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
		{
			/* При отрицательном ответе делаем откат действий
			 * и закрываем диалог без удаления записи
			 * */
			//QSqlDatabase::database().rollback();
			return;
		} else {
			/* В противном случае производим удаление записи.
			 * При успешном удалении обновляем таблицу.
			 * */
			ui->packet1TableWidget->removeRow(row);
//			modelDevice->select();
//			ui->deviceTableView->setCurrentIndex(modelDevice->index(-1, -1));
		}
	}
}
void MainWindow::cellSelected(int row, int col)
{
	QMessageBox::information(this, "",
	 "Cell at row " + QString::number(row) +
	 " column " + QString::number(col) +
	 " was double clicked.");
	QString name = ui->scenarioTableWidget->itemAt(row, col)->data(Qt::DisplayRole).toString();
	if (currentWidget) currentWidget->hide();
}

void MainWindow::cellPressed(int row, int col)
{
	 qDebug() << "Cell at row " + QString::number(row) +
	 " column " + QString::number(col) + " was pressed.";
	QString name = ui->scenarioTableWidget->itemAt(row, col)->data(Qt::DisplayRole).toString();
	if (currentWidget) currentWidget->hide();

	for (int i = 0; i < ui->selectLayout->count(); ++i)	{
		QLayoutItem *wItem = ui->selectLayout->layout()->takeAt(i);
		if (wItem != nullptr) {
			delete wItem;
		}
	}
	ActionWidgetBase *wdgt = widgetFactory_.Create(
				ui->scenarioTableWidget->item(row, col)->data(Qt::DisplayRole).toString());
	currentWidget = wdgt;
	ui->selectLayout->addWidget(wdgt);
	wdgt->show();
}

//void MainWindow::fillActions(QList<QString> &names)
//{
//	int _row = 0;
//	foreach (auto str, names) {
//		ICreator* action = _factory->getCreatorByName(str);
//		Q_ASSERT( action );
//		action->widget()->hide();

//		QTableWidgetItem *item = new QTableWidgetItem(action->name());

//		item->setFlags(Qt::ItemIsSelectable|
//					   Qt::ItemIsDragEnabled|
//					   Qt::ItemIsDropEnabled|
//					   Qt::ItemIsUserCheckable|
//					   Qt::ItemIsEnabled);

//		ui->actionTableWidget->insertRow(_row);
//		ui->actionTableWidget->setItem(_row++, 0, item);
//	}
////	TcpHeader *header = new TcpHeader(this);
////	IAction *client = new IAction (this);
////	createItemFromAction(client, "Client", header);


////	ServerWidget * serverWidget = new ServerWidget(this);
////	IAction *server = new IAction (this);
////	createItemFromAction(server, "Server", serverWidget);


////	//connect(_client, &ClientAction::triggered, this, &MainWindow::onClientAction);
//////	connect(act, &QAction::triggered, this, &MainWindow::onTriggered);
//////	connect(act, &QAction::hovered, this, &MainWindow::onTriggered);
////	ui->actionTableWidget->resizeColumnsToContents();
////	connect(ui->actionTableWidget, &QTableWidget::cellClicked, this,  &MainWindow::onActionPressed);
//////	connect(ui->actionTableWidget, &QTableWidget::cellPressed, this,  &MainWindow::onActionPressed);
//	//	ui->actionTableWidget->addActions(_actions); // ?????? как быть с
//}

void MainWindow::fillTable(QTableWidget *widget, QList<QString> &names)
{
	int _row = 0;
	foreach (auto item, names) {
		QTableWidgetItem *it = new QTableWidgetItem(item);

		widget->insertRow(_row);
		widget->setItem(_row++, 0, it);
	}
}

void MainWindow::on_actionRun_triggered()
{
	Controller *cont = new Controller(&scenActions_, &context_);

}
