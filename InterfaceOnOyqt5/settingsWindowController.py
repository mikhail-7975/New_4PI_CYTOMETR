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

    def readMessageFromPort(self):
        message = ""
        inp = b''
        while cytometr.serialPort.inWaiting():
            inp = cytometr.serialPort.  read()
            message += inp.decode('utf-8')
        return message

    @QtCore.pyqtSlot()
    def setButtonCliked(self):
        print("set button")
        if cytometr.serialPortStatus == portStatuses.connect:
            print(self.readMessageFromPort())
            cytometr.serialPort.write(b'Gain')
            inp = self.readMessageFromPort()
            if inp == "Enter value (0-4095)\r\n":
                print(self.gainLineEdit.text().encode())
                cytometr.serialPort.write(b'1')
        else:
            print("cytometr disconnected")
