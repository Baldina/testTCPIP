#ifndef TCPPACKET_H
#define TCPPACKET_H

#include <QWidget>

namespace Ui {
class TcpPacket;
}

const int tcpHeaderMinBytes = 20;
const int tcpHeaderMaxBytes = 60;

class TcpPacket : public QWidget
{
    Q_OBJECT
    struct Header {
        quint16 srcPort;
        quint16 destPort;
        quint32 sequNumber;
        quint32 ackNumber;
        unsigned int headLength:4;// Header length = Header length field value x 4 bytes
        unsigned int urgFlags:1;
        unsigned int ackFlags:1;
        unsigned int pshFlags:1;
        unsigned int rstFlags:1;
        unsigned int synFlags:1;
        unsigned int finFlags:1;
        quint16 windowSize;
        quint16 checkSum;
        //quint16 urgentOffset;
    };

public:
    explicit TcpPacket(QWidget *parent = nullptr);
    ~TcpPacket();

private:
    Ui::TcpPacket *ui;
};

#endif // TCPPACKET_H
