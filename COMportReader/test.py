import serial
import pyqtgraph as pg
import random
from PyQt5 import QtGui, QtWidgets,QtCore
from PyQt5.QtWidgets import QWidget, QApplication
from pyqtgraph.Qt import QtGui, QtWidgets,QtCore
from threading import Thread
'''
app = QtGui.QApplication([])

win = pg.GraphicsLayoutWidget(show=True, title="Basic plotting examples")
win.resize(800, 600)
win.setWindowTitle('comPortReader')

p = win.addPlot(title="Updating plot")
curve = p.plot(pen='y')

inpFromComPort = 0

def update():
    global curve, data, inpFromPort
    data.pop(0)
    data.append(inpFromPort)
    inpFromPort = random.randint(0, 100)
    curve.setData(data)
    p.enableAutoRange('xy', True)
'''
class TestWidget(QWidget):
    def __init__(self, parent = None):
        QWidget.__init__(self, parent)

    def keyPressEvent(self, event):
        print("pressed key " + str(event.key()))

if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
    tst = TestWidget()
    tst.show()
    sys.exit(app.exec_())