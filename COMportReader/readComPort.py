import serial
import pyqtgraph as pg
from pyqtgraph.Qt import QtGui, QtCore
from threading import Thread

inpFromPort = 0

class ComPortReaderThread(Thread):
   def __init__(self, portName):
        """Инициализация потока"""
        Thread.__init__(self)
        self.name = portName
        self.serialPort = serial.Serial(portName)

   def run(self):
        """Запуск потока"""
        global inpFromPort
        while(1):
            inp0, inp1 = self.serialPort.read(), self.serialPort.read()
            #data1 = ord(inp0)  # .decode('utf-8')) << 8)
            #data2 = ord(inp1)  # .decode('utf-8')
            #print(bin((data1 << 8 | data2))[2:].zfill(16))
            inpFromPort = ((ord(inp0) << 8) | ord(inp1))
            print(inpFromPort)

app = QtGui.QApplication([])

win = pg.GraphicsLayoutWidget(show=True, title="Basic plotting examples")
win.resize(800, 600)
win.setWindowTitle('comPortReader')

p = win.addPlot(title="Updating plot")
curve = p.plot(pen='y')
#x = np.arange(0, 3*np.pi, 0.1)
data = [0.] * 200#np.sin(x)

def update():
    global curve, data, inpFromPort

    #inp0, inp1 = s.read(), s.read()
    #data1 = ord(inp0)  # .decode('utf-8')) << 8)

    #data2 = ord(inp1)  # .decode('utf-8')
    #print(bin((data1 << 8 | data2))[2:].zfill(16))
    data.pop(0)
    data.append(inpFromPort)
    curve.setData(data)
    p.enableAutoRange('xy', True)





timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(100)

#while(1):

#0011 1111 // 1100 | 0011 // 1111 1100 | 0011 1111 1100| 0011 1111 1100

#print("end")

if __name__ == '__main__':
    import sys
    portReader = ComPortReaderThread('COM11')
    portReader.start()
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):

        QtGui.QApplication.instance().exec_()

portReader.join()