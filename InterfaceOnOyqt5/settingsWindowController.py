from settingsWindow import *
from CytometrKernel import *



class settingsWindowController(QtWidgets.QDialog, Ui_SettingsWindow):
    def __init__(self, parent = None):
        super(settingsWindowController, self).__init__(parent)
        self.setupUi(self)
        self.connectPushButton.clicked.connect(self.connectButtonCliked)
        self.setParamsPushButton.clicked.connect(self.setButtonCliked)

    @QtCore.pyqtSlot()
    def connectButtonCliked(self):
        print("connect button")
        try:
            if cytometr_kernel.triggerPortStatus == portStatuses.disconnect:
                triggerPortName = self.triggerPortNameLineEdit.text()# portNameLineEdit.text()
                tracerPortName = self.tracerPortNameLineEdit.text()
                cytometr_kernel.connectToPort(triggerPortName)
                cytometr_kernel.connectToPort(tracerPortName)
                self.connectPushButton.setText("Disconnect")
                #cytometr_kernel.triggerSerialPort.write(b'w')
            else:
                cytometr_kernel.triggerSerialPort.close()
                cytometr_kernel.tracerSerialPort.close()
                cytometr_kernel.tracerSerialPort = None
                cytometr_kernel.triggerSerialPort = None
                cytometr_kernel.triggerPortStatus = portStatuses.disconnect
                self.connectPushButton.setText("Connect")
        except Exception as e:
            print(e)

    @QtCore.pyqtSlot()
    def setButtonCliked(self):
        print("set button")

        message = "g" + self.gainLineEdit.text().zfill(4) + "t" + self.triggerLowLineEdit.text().zfill(4)
        print(message)
        print(message.encode('utf-8'))
        if cytometr_kernel.triggerPortStatus == portStatuses.connect:
            cytometr_kernel.gain = int(self.gainLineEdit.text())
            cytometr_kernel.triggerLevel = int(self.triggerLowLineEdit.text())
            cytometr_kernel.triggerSerialPort.write(message.encode('utf-8'))
        else:
            print("cytometr disconnected")
