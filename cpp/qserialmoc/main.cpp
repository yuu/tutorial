#include <QApplication>
#include <QSerialPort>
#include <QObject>
#include <QtDebug>

#include "serialportmoc.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSerialPort *port = new SerialPortMoc();
    QObject::connect(port, &QSerialPort::readyRead,
                     [&port, &app] {
                         qDebug() << qobject_cast<SerialPortMoc*>(port)->readAll();
                         exit(0);
                     });

    qobject_cast<SerialPortMoc*>(port)->enqueue(QByteArray("aaaa"));

    return app.exec();
}
