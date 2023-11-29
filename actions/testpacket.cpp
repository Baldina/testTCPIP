#include "testpacket.h"

TestPacket::TestPacket()
{

}

QString TestPacket::name() const
{
	return _name;
}

void TestPacket::setName(const QString &name)
{
	_name = name;
}
int TestPacket::size() const
{
	return _data.size();
}

void TestPacket::setSize(const int len)
{
	_data.resize(len);
}
