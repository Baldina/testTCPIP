#ifndef TESTPACKTE_H
#define TESTPACKTE_H

#include <QObject>

class TestPacket
{
public:
	TestPacket();

	QString name() const;
	void setName(const QString &name);

	int size() const;
	void setSize(const int len);

private:
	QString _name;
	QByteArray _data;
};

#endif // TESTPACKTE_H
