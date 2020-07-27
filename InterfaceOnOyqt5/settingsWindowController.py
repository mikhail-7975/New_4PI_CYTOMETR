from settingsWindow import *
from CytometrKernel import *
import serial
import serial.tools.list_ports



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
                if portName == "":
                    ports = serial.tools.list_ports.comports(include_links=False)
                    cytometr.serialPort = serial.Serial(ports[0].device)
                    self.portNameLineEdit.setText(ports[0].device)
                else:
                    cytometr.serialPort = serial.Serial(portName)
                cytometr.serialPortStatus = portStatuses.connect
                self.connectPushButton.setText("Disconnect")
                cytometr.serialPort.write(b'w')
            else:
                cytometr.serialPort.close()
                cytometr.serialPortStatus = portStatuses.disconnect
                self.connectPushButton.setText("Connect")
        except Exception as e:
            print(e)

    def readDataFromPort(self):
        data = []
        while (data.inWaiting()):
            str.append(ord(data.read()) | (ord(data.read()) << 8))
        return data

    @QtCore.pyqtSlot()
    def setButtonCliked(self):
        print("set button")

        message = "g" + self.gainLineEdit.text().zfill(4) + "t" + self.triggerLowLineEdit.text().zfill(4)
        print(message)
        print(message.encode('utf-8'))
        if cytometr.serialPortStatus == portStatuses.connect:
            cytometr.gain = int(self.gainLineEdit.text())
            cytometr.triggerLevel = int(self.triggerLowLineEdit.text())
            cytometr.serialPort.write(message.encode('utf-8'))
        else:
            print("cytometr disconnected")
