from mainWindow import *
from settingsWindowController import *

class mainWindowController(QtWidgets.QDialog, Ui_MainWindow):
    def __init__(self, parent = None):
        super(mainWindowController, self).__init__(parent)
        self.setupUi(self)
        self.settingsPushButton.clicked.connect(self.settingsButtonCliked)
        self.startReadingPushButton.clicked.connect(self.startReadingCliked)
        self.stopReadingPushButton.clicked.connect(self.stopReadingCliked)

    @QtCore.pyqtSlot()
    def settingsButtonCliked(self):
        settingsWindow = settingsWindowController()
        settingsWindow.exec_()

    @QtCore.pyqtSlot()
    def startReadingCliked(self):
        if cytometr_kernel.serialPortStatus == portStatuses.connect:
            cytometr_kernel.status = cytoStatuses.readData
            cytometr_kernel.serialPort.write(b'r')
        else:
            print("cytometr disconnected")

    @QtCore.pyqtSlot()
    def stopReadingCliked(self):
        if cytometr_kernel.serialPortStatus == portStatuses.connect:
            cytometr_kernel.status = cytoStatuses.notReadData
            cytometr_kernel.serialPort.write(b's')
        else:
            print("cytometr disconnected")



#100 ч/с * 5000 точек/ч * 2 байта/точку = 0.95 мбайт/с - без разделителей
#100 ч/с * 5000 точек/ч * 3 байта/точку = 1.5 мбайт/с - с разделителями

#время пролёта частицы - 1 мс
#время между частицами - ~1 мс

#1 ms - 5000 ptr => 