from settingsWindow import *
from CytometrKernel import *
import serial



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
            if cytometr.serialPortStatus == portStatuses.disconnect:
                portName = self.portNameLineEdit.text()
                cytometr.serialPort = serial.Serial(portName)
                cytometr.serialPortStatus = portStatuses.connect
                self.connectPushButton.setText("Disconnect")
            else:
                cytometr.serialPort.close()
                cytometr.serialPortStatus = portStatuses.disconnect
                self.connectPushButton.setText("Connect")
        except:
            print("exception")

    def readMessageFromPort(self):
        message = ""
        inp = b''
        byteCount = 0
        while cytometr.serialPort.inWaiting():
            inp = cytometr.serialPort.  read()
            #if inp == b'\n':
            #    break
            message += inp.decode('utf-8')
        return message

    @QtCore.pyqtSlot()
    def setButtonCliked(self):
        print("set button")
        cytometr.serialPort.write(b'w')
        print(self.readMessageFromPort())
        cytometr.serialPort.write(b'Gain')
        print(self.readMessageFromPort())
        cytometr.serialPort.write(b'1')