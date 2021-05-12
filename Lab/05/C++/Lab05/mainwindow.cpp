#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->LoadButton, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(ui->SaveButton, &QPushButton::clicked, this, &MainWindow::saveImage);
    connect(ui->EncodeButton, &QPushButton::clicked, this, &MainWindow::encodeMsg);
    connect(ui->DecodeButton, &QPushButton::clicked, this, &MainWindow::decodeMsg);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::msgChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Допустимые форматы (*.png)");
    if (!fileName.isEmpty()){
        if (image.load(fileName)){
            image.convertTo(QImage::Format_ARGB32);
            ui->label->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Изображение загруженно!</span></p></body></html>");
        }
        else ui->label->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Изображение не загруженно!</span></p></body></html>");
    }
}

void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "Допустимые форматы (*.png)");
    if (!fileName.isEmpty()){
            if (image.save(fileName)){
                ui->label->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Изображение успешно сохраненно!</span></p></body></html>");
            }
            else ui->label->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Изображение не сохраненно!</span></p></body></html>");
    }
}

QString byteArrayToBitString(const QByteArray& bytes){
    QString bitString;
    for (unsigned char byte : bytes) {
        bitString += QString("%1").arg(byte, 8, 2, QChar('0'));
    }
    return bitString;
}

 QByteArray bitStringToByteArray(const QString bitString){
    QByteArray byteArray(bitString.size()/8, 0);
    bool ok;
    for(int i=0; i<byteArray.size(); i++) {
        byteArray[i] = bitString.mid(i*8, 8).toUInt(&ok, 2);
        if (!ok) qDebug() << "Error bitStringToByteArray";
    }
    return byteArray;
}

void MainWindow::encodeMsg()
{
    QString msg = byteArrayToBitString(QString("❤").toUtf8());
    msg += QString("%1").arg(ui->plainTextEdit->toPlainText().toUtf8().size(), 32, 2, QChar('0'));
    msg += byteArrayToBitString(ui->plainTextEdit->toPlainText().toUtf8());


    if (((image.width()*image.height())*3/8) >= (msg.length()/8)){
        int lenghtMsg = 0;
        for (int y = 0; y < image.height(); y++){
            if (lenghtMsg > msg.length()){
                break;
            }
            for (int x = 0; x < image.width(); x++){
                QColor pixel;
                qDebug() << (msg[lenghtMsg].unicode()-48);
                if (lenghtMsg < msg.length()){
                    if(image.pixelColor(x, y).red()%2 != 0){
                        pixel.setRed(image.pixelColor(x, y).red()-1+(msg[lenghtMsg].unicode()-48));
                    }
                    else pixel.setRed(image.pixelColor(x, y).red()+(msg[lenghtMsg].unicode()-48));
                }
                else pixel.setRed(image.pixelColor(x, y).red());

                lenghtMsg++;
                if (lenghtMsg < msg.length()){
                    if(image.pixelColor(x, y).green()%2 != 0){
                        pixel.setGreen(image.pixelColor(x, y).green()-1+(msg[lenghtMsg].unicode()-48));
                    }
                    else pixel.setGreen(image.pixelColor(x, y).green()+(msg[lenghtMsg].unicode()-48));
                }
                else pixel.setGreen(image.pixelColor(x, y).green());

                lenghtMsg++;
                if (lenghtMsg < msg.length()){
                    if(image.pixelColor(x, y).blue()%2 != 0){
                        pixel.setBlue(image.pixelColor(x, y).blue()-1+(msg[lenghtMsg].unicode()-48));
                    }
                    else pixel.setBlue(image.pixelColor(x, y).blue()+(msg[lenghtMsg].unicode()-48));
                }
                else pixel.setBlue(image.pixelColor(x, y).blue());

                image.setPixelColor(x,y,pixel);

                lenghtMsg++;

                if (lenghtMsg > msg.length()){
                    break;
                }
            }
        }
        ui->label->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Сообщение добавлено в картинку!</span></p></body></html>");
    }
    else ui->label->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Ошибка. Не достаточно места!</span></p></body></html>");
}

void MainWindow::decodeMsg()
{
        QString msg;

        QVector<QColor> array;

        for (int y = 0; y < image.height(); y++){
            for (int x = 0; x < image.width(); x++){
                array.append(image.pixelColor(x,y));
            }
        }

        for (int i = 0; i < array.length(); i++){
            if(array[i].red()%2 != 0) msg.append('1');
            else msg.append('0');

            if(array[i].green()%2 != 0) msg.append('1');
            else msg.append('0');

            if(array[i].blue()%2 != 0) msg.append('1');
            else msg.append('0');
        }

        bool ok;

        if (bitStringToByteArray(msg.mid(0, 24)) == QString("❤").toUtf8()){
            auto size = msg.mid(24, 32).toUInt(&ok, 2);

            ui->plainTextEdit->setPlainText(QString("Размер сообщения %1 байт\n").arg(size));
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + QString::fromUtf8(bitStringToByteArray(msg.mid(24+32, size*8))));
        }else{
             ui->plainTextEdit->setPlainText("Метка не найдена");
        }

}

void MainWindow::msgChanged()
{
    int pool = (image.width()*image.height())*3/8;
    int text = (ui->plainTextEdit->toPlainText().toUtf8().length() + 3 + 4);
    ui->label->setText(QString("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Ещё можно ввести: %1 байт!</span></p></body></html>").arg(pool-text));

}



