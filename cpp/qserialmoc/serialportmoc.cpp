#include "serialportmoc.h"

QByteArray SerialPortMoc::readAll() {
    return buffer.dequeue();
}

void SerialPortMoc::enqueue(QByteArray buf) {
    buffer.enqueue(buf);
    emit readyRead();
}
