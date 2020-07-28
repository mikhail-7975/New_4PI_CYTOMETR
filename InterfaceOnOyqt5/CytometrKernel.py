import serial
import serial.tools.list_ports

class portStatuses:
    disconnect = 0
    connect = 1
    problems = 2

class cytoStatuses:
    off = -1
    on = 0
    notReadData = 1
    readData = 2



class cytometr_kernel:
    serialPort = None
    serialPortStatus = portStatuses.disconnect
    status = cytoStatuses.notReadData
    gain = 0
    triggerLevel = 0

    dataList = [] #list of list with experimental datas

    def connectToPort(self, portName = ""):
        if portName == "":
            ports = serial.tools.list_ports.comports(include_links=False)
            cytometr_kernel.serialPort = serial.Serial(ports[0].device)
            self.portNameLineEdit.setText(ports[0].device)
        else:
            cytometr_kernel.serialPort = serial.Serial(portName)
        cytometr_kernel.serialPortStatus = portStatuses.connect

    def readDataFromPort(self):
        data = []
        while (data.inWaiting()):
            str.append(ord(data.read()) | (ord(data.read()) << 8))
        return data
