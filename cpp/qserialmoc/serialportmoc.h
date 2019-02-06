#pragma once

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include <QQueue>

class SerialPortMoc : public QSerialPort {
Q_OBJECT

public:
    QByteArray readAll();

public:
    void enqueue(QByteArray buf);

private:
    QQueue<QByteArray> buffer;
};
