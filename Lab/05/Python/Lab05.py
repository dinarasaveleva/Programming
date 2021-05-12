from PySide6.QtCore import *
from PySide6.QtGui import *
from PySide6.QtWidgets import *


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(480, 250)
        MainWindow.setMinimumSize(QSize(480, 250))
        MainWindow.setMaximumSize(QSize(480, 250))
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.formLayout = QFormLayout(self.centralwidget)
        self.formLayout.setObjectName(u"formLayout")
        self.plainTextEdit = QPlainTextEdit(self.centralwidget)
        self.plainTextEdit.setObjectName(u"plainTextEdit")

        self.formLayout.setWidget(2, QFormLayout.LabelRole, self.plainTextEdit)

        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, -1, -1)
        self.LoadButton = QPushButton(self.centralwidget)
        self.LoadButton.setObjectName(u"LoadButton")
        sizePolicy = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.LoadButton.sizePolicy().hasHeightForWidth())
        self.LoadButton.setSizePolicy(sizePolicy)

        self.verticalLayout_2.addWidget(self.LoadButton)

        self.SaveButton = QPushButton(self.centralwidget)
        self.SaveButton.setObjectName(u"SaveButton")
        sizePolicy.setHeightForWidth(self.SaveButton.sizePolicy().hasHeightForWidth())
        self.SaveButton.setSizePolicy(sizePolicy)

        self.verticalLayout_2.addWidget(self.SaveButton)

        self.EncodeButton = QPushButton(self.centralwidget)
        self.EncodeButton.setObjectName(u"EncodeButton")
        sizePolicy.setHeightForWidth(self.EncodeButton.sizePolicy().hasHeightForWidth())
        self.EncodeButton.setSizePolicy(sizePolicy)

        self.verticalLayout_2.addWidget(self.EncodeButton)

        self.DecodeButton = QPushButton(self.centralwidget)
        self.DecodeButton.setObjectName(u"DecodeButton")
        sizePolicy.setHeightForWidth(self.DecodeButton.sizePolicy().hasHeightForWidth())
        self.DecodeButton.setSizePolicy(sizePolicy)

        self.verticalLayout_2.addWidget(self.DecodeButton)


        self.formLayout.setLayout(2, QFormLayout.FieldRole, self.verticalLayout_2)

        self.label = QLabel(self.centralwidget)
        self.label.setObjectName(u"label")

        self.formLayout.setWidget(1, QFormLayout.SpanningRole, self.label)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.plainTextEdit.setPlaceholderText(QCoreApplication.translate("MainWindow", u"\u0412\u0432\u0435\u0434\u0438\u0442\u0435 \u0442\u0435\u043a\u0441\u0442", None))
        self.LoadButton.setText(QCoreApplication.translate("MainWindow", u"\u0417\u0430\u0433\u0440\u0443\u0437\u0438\u0442\u044c \u043a\u0430\u0440\u0442\u0438\u043d\u043a\u0443", None))
        self.SaveButton.setText(QCoreApplication.translate("MainWindow", u"\u0421\u043e\u0445\u0440\u0430\u043d\u0438\u0442\u044c \u043a\u0430\u0440\u0442\u0438\u043d\u043a\u0443", None))
        self.EncodeButton.setText(QCoreApplication.translate("MainWindow", u"\u041a\u043e\u0434\u0438\u0440\u043e\u0432\u0430\u0442\u044c \u0442\u0435\u043a\u0441\u0442", None))
        self.DecodeButton.setText(QCoreApplication.translate("MainWindow", u"\u0414\u0435\u043a\u043e\u0434\u0438\u0440\u043e\u0432\u0430\u0442\u044c \u0442\u0435\u043a\u0441\u0442", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">\u041b\u0430\u0431\u043e\u0440\u0430\u0442\u043e\u0440\u043d\u0430\u044f \u0440\u0430\u0431\u043e\u0442\u0430 \u21165</span></p></body></html>", None))
    # retranslateUi


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.image = QImage()
        self.ui.LoadButton.clicked.connect(self.loadImage)
        self.ui.SaveButton.clicked.connect(self.saveImage)
        self.ui.EncodeButton.clicked.connect(self.encodeMsg)
        self.ui.DecodeButton.clicked.connect(self.decodeMsg)
        
    def bitStringToByteArray(self, bitString):
        return int(bitString, 2).to_bytes(int(len(bitString)/8), byteorder='big')
    
    def byteArrayToBitString(self, bytess):
        string = bin(int(bytess.hex(), base=16))[2:].zfill(8)
        if (len(string)%2 != 0):
            string = '0' + string
        return string
    
    def createLenByteString(self, byteString):
        return bin(int(hex(len(byteString)).split('x')[-1], base=16))[2:].zfill(32)
    
    @Slot()
    def loadImage(self):
        fileName, _ = QFileDialog.getOpenFileName(self, "Open Image", "", "Доступные форматы (*.png)")
        if len(fileName) != 0:
            if self.image.load(fileName):
                self.image.convertTo(QImage.Format_ARGB32)
                self.ui.label.setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Изображение загруженно!</span></p></body></html>")
            else:
                self.ui.label.setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Изображение не загруженно!</span></p></body></html>")
    
    @Slot()
    def saveImage(self):
        fileName, _ = QFileDialog.getSaveFileName(self, "Save Image", "", "Доступные форматы (*.png)")
        if len(fileName) != 0:
            if self.image.save(fileName):
                self.ui.label.setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\"></span></p></body></html>")
            else:
                self.ui.label.setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Изображение не сохраненно!</span></p></body></html>")
    
    @Slot()
    def encodeMsg(self):
        msg = self.byteArrayToBitString('❤'.encode('utf-8'))
        msg += self.createLenByteString(self.ui.plainTextEdit.toPlainText().encode('utf-8'))
        msg += self.byteArrayToBitString(self.ui.plainTextEdit.toPlainText().encode('utf-8'))
               
        if (self.image.width()*self.image.height())*3/8 >= (len(msg)/8):
            lenghtMsg = 0
            for y in range(self.image.height()):
                if lenghtMsg > len(msg):
                    break
                for x in range(self.image.width()):
                    pixel = QColor()
                    if lenghtMsg < len(msg):
                        if self.image.pixelColor(x, y).red()%2 != 0:
                            pixel.setRed(self.image.pixelColor(x, y).red()-1+int(msg[lenghtMsg]))
                        else: pixel.setRed(self.image.pixelColor(x, y).red()+int(msg[lenghtMsg]))
                    else: pixel.setRed(self.image.pixelColor(x, y).red())
                    
                    lenghtMsg += 1
                    if lenghtMsg < len(msg):
                        if self.image.pixelColor(x, y).green()%2 != 0:
                            pixel.setGreen(self.image.pixelColor(x, y).green()-1+int(msg[lenghtMsg]))
                        else: pixel.setGreen(self.image.pixelColor(x, y).green()+int(msg[lenghtMsg]))
                    else: pixel.setGreen(self.image.pixelColor(x, y).green())
                    
                    lenghtMsg += 1
                    if lenghtMsg < len(msg):
                        if self.image.pixelColor(x, y).blue()%2 != 0:
                            pixel.setBlue(self.image.pixelColor(x, y).blue()-1+int(msg[lenghtMsg]))
                        else: pixel.setBlue(self.image.pixelColor(x, y).blue()+int(msg[lenghtMsg]))
                    else: pixel.setBlue(self.image.pixelColor(x, y).blue())
                    
                    self.image.setPixelColor(x, y, pixel)
                    lenghtMsg += 1
                    
                    if lenghtMsg > len(msg):
                        break
            self.ui.label.setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Сообщение добавлено в картинку!</span></p></body></html>")
        else: 
            self.ui.label.setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">Ошибка. Не достаточно места!</span></p></body></html>")

    @Slot()
    def decodeMsg(self):
        msg = ''
        array = []
        
        for y in range(self.image.height()):
            for x in range(self.image.width()):
                array.append(self.image.pixelColor(x,y))
        
        for i in range(len(array)):
            if array[i].red()%2 != 0:
                msg += '1'
            else:
                msg += '0'
            if array[i].green()%2 != 0:
                msg += '1'
            else:
                msg += '0'
            if array[i].blue()%2 != 0:
                msg += '1'
            else:
                msg += '0'
                        
        if self.bitStringToByteArray(msg[:24]) == "❤".encode('utf-8'):
            size = int.from_bytes(self.bitStringToByteArray(msg[24:56]), byteorder='big')
            self.ui.plainTextEdit.setPlainText('Размер сообщения %s байт\n' % size)
            self.ui.plainTextEdit.setPlainText(self.ui.plainTextEdit.toPlainText() + self.bitStringToByteArray(msg[56:(56+size*8)]).decode('utf-8'))
        else:
            self.ui.plainTextEdit.setPlainText('Метка не найдена!\n')

if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
  
    window = MainWindow()
    window.show()
  
    sys.exit(app.exec_())