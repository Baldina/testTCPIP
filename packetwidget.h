#ifndef PACKETWIDGET_H
#define PACKETWIDGET_H

#include <QWidget>

namespace Ui {
class PacketWidget;
}

class PacketWidget : public QWidget
{
	Q_OBJECT

	explicit PacketWidget(QWidget *parent = nullptr); // private

public:
		static PacketWidget* instance() {
			static PacketWidget * _instance = nullptr;
			if ( _instance == nullptr ) {
				_instance = new PacketWidget();
			}
			return _instance;
		}

public:
	~PacketWidget();

public slots:
	void browse();
private:
	Ui::PacketWidget *ui;
};

#endif // PACKETWIDGET_H
