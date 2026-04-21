#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QProcess>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->portCombo->addItem("ttyACM0");
    ui->portCombo->addItem("ttyACM1");
    ui->baudCombo->addItem("9600");
    ui->baudCombo->addItem("115200");
}

MainWindow::~MainWindow()
{
    delete ui;
}

qint64 MainWindow::getSerialPortPID(QString portPath) {
    QProcess process;
    // -t 옵션: PID만 출력, -u: 특정 파일 점유 확인
    process.start("lsof", QStringList() << "-t" << portPath);
    process.waitForFinished();

    QString output = process.readAllStandardOutput().trimmed();

    if (output.isEmpty()) {
        return 0; // 점유 중인 프로세스 없음
    }

    return output.toLongLong(); // 점유 중인 프로세스의 PID 반환
}


void MainWindow::on_connectButton_clicked()
{
    QString portName = ui->portCombo->currentText();
    int baud = ui->baudCombo->currentText().toInt();


    serial=new QSerialPort(this);
    serial->setPortName(portName);
    serial->setBaudRate(baud);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    // 사용 예
    QString port = "/dev/ttyACM0";
    qint64 pid = getSerialPortPID(port);

    if (pid > 0) {
        qDebug() << port << "는 현재 사용 중입니다. PID:" << pid;
    } else {
        if( serial->open(QIODevice::ReadWrite) ) {
            ui->textBrowser->append("Connection : Port Opened!");
        } else {
            ui->textBrowser->append("Connection : Port Opened ERROR!");
        }
    }




    //////////////////
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);

}



void MainWindow::readData() {
    //m_buffer.append(serial->readAll());
    m_buffer += serial->readAll();

    while(m_buffer.contains('$') && m_buffer.contains('#')){
        int start = m_buffer.indexOf('$');
        int end = m_buffer.indexOf('#', start);

        if (end == -1) break;
        QByteArray packet = m_buffer.mid(start+1, end-start-1);
        m_buffer.remove(0, end + 1);

        if (!packet.isEmpty()) {
            ui ->textBrowser->append(packet);
            parseProtocol(packet);

        }
    }

    // QByteArray data;
    // while(m_buffer.contains('\n')){

    //     int newLineIndex = m_buffer.indexOf('\n');
    //     data = m_buffer.left(newLineIndex);
    //     m_buffer.remove(0, newLineIndex+1);

    //     if(data.endsWith('\r')){
    //         data.chop(1);
    //     }



    //     if(data.isEmpty() == false) {
    //         ui->textBrowser->append(data);
    //     }
    // }
}

void MainWindow::parseProtocol(const QByteArray &packet){
    QString data = QString::fromUtf8(packet);
    QStringList parts = data.split(',');

    if(parts.size() < 2) return;

    // parts[0] is data count;
    for(int i = 1 ; i < parts.size(); ++i){
        QStringList item = parts[i].split(':');
        if( item.size() < 3) continue;
        int sensorID = item[0].toInt();
        int dataType = item[1].toInt();

        QString valueStr = item[2];

        if(sensorID == ID_ENV_TEMP) {
            //ui->textBrowser->append(QString::number(sensorID));
            //ui->textBrowser->append(QVariant(sensorType).toString());
           // ui->textBrowser->append(valueStr);

            ui->tempValue->setText(valueStr + "ºC");
        } else if(sensorID == ID_OUT_LED_STATE) {
            ui->ledValue->setText(valueStr);
        }
    }
}

void MainWindow::on_monitorStartButton_clicked()
{
    if(serial->isOpen()){
        QString str = "mon on 100\r\n";

        qint64 bytesWritten = serial->write(str.toUtf8());

        serial->flush();;
        if(bytesWritten == -1){
            ui->textBrowser->append("Transmit Error!!");
        } else {
            ui->textBrowser->append("TX -> " + str);
        }
    }
}


void MainWindow::on_monitorStopButton_clicked()
{
    if(serial->isOpen()){
        QString str = "mon off\r\n";
        qint64 bytesWritten = serial->write(str.toUtf8());
        serial->flush();;


        if(bytesWritten == -1){
            ui->textBrowser->append("Transmit Error!!");
        } else {
            ui->textBrowser->append("TX -> " + str);
        }
    }
}


void MainWindow::on_ledBlinkButton_clicked()
{
    if(serial->isOpen()){

        QString str = "led toggle 1000\r\n";


        qint64 bytesWritten = serial->write(str.toUtf8());

        serial->flush();;
        if(bytesWritten == -1){
            ui->textBrowser->append("Transmit Error!!");
        } else {
            ui->textBrowser->append("TX -> " + str);
        }
    }
}




