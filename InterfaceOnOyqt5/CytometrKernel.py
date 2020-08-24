import serial
import serial.tools.list_ports
from settingsWindow import Ui_SettingsWindow


class portStatuses:
    disconnect = 0
    connect = 1
    problems = 2

class cytoStatuses:
    off = -1
    on = 0
    notReadData = 1
    readData = 2
    writingInFile = 3

class comPortCommands:
    gain = "0x01"
    triggerLevel = "0x10"
    startDraw = "Start Draw"
    class experiment:
        startTrigger = "0x04"
        startTracer = "0x03"
    class debug:
        start = "0x02"
    stop = "0x05"
    resetNumber = "0x6"

    startTracer = "Start Tracer"
    reset = "Reset"

'''0x01XXXX - Gain setting, XXXX - Value 0x0000 - 0x0FFF (0 - 4095)
   0x10XXXX - Trigger level setting, XXXX - Value 0x0000 - 0x0FFF (0 - 4095)
   0x02 - Start Streaming mode sending debug traces (without external interrupt from tigger)
   0x03 - Start Tracer mode sending traces (with external interrupt from tigger)
   0x04 - Sart Trigger mode (sending trigger impulse)
   0x05 - Stop Stream\Tracer\Trigger mode
   0x06 - Reset Number of trace'''


class cytometr_kernel:
    triggerSerialPort = None
    tracerSerialPort = None
    triggerPortStatus = portStatuses.disconnect
    tracerPortStatus = portStatuses.disconnect
    status = cytoStatuses.notReadData
    gain = 0
    triggerLevel = 0

    dataList = [] #list of list with experimental datas
    fileCounter = 0

    def setTriggerLevel(self, trigLevel):
        return 0

    def setGain(self, gainCoef):
        return 0

    def connectToPort(self, portName = ""):
        if portName == "":
            ports = serial.tools.list_ports.comports(include_links=False)
            cytometr_kernel.triggerSerialPort = serial.Serial(ports[0].device)
            Ui_SettingsWindow.triggerPortNameLineEdit.setText(ports[0].device)
            cytometr_kernel.tracerSerialPort = serial.Serial(ports[1].device)
            Ui_SettingsWindow.triggerPortNameLineEdit.setText(ports[1].device)
        else:
            cytometr_kernel.triggerSerialPort = serial.Serial(portName)
        cytometr_kernel.triggerPortStatus = portStatuses.connect

    def readDataFromPort(self, port):
        data = []
        while (port.inWaiting()):
            data.append(ord(port.read()) | (ord(port.read()) << 8))
        return data
